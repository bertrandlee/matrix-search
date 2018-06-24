#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "MyMatrix.h"

#define XOR_MASK 0xffffffff
#define ENCRYPT_DATA 1


MyMatrix::MyMatrix()
{
    m_pMatrix = NULL;
    m_rowCount = 0;
    m_colCount = 0;
    m_valCount = 0;
}

MyMatrix::~MyMatrix()
{
    if (m_pMatrix != NULL)
    {
        delete [] m_pMatrix;
    }
}

void MyMatrix::SetDimensions(int rowCount, int colCount)
{
    if (rowCount <= 0 || colCount <= 0)
    {
        throw std::invalid_argument("Invalid row or col count");
    }
    
    m_rowCount = rowCount;
    m_colCount = colCount;
    m_valCount = (long long) rowCount * (long long) colCount;
        
    if (m_valCount / m_rowCount != m_colCount)
    {
        throw std::invalid_argument("Matrix element count too large");
    }
}

void MyMatrix::ReadFromBinFile(char *fileName)
{
    std::ifstream file;
    int rowCount, colCount;
    
    file.open(fileName, std::ios::binary);
    file.read((char*) &rowCount, sizeof(rowCount));
    file.read((char*) &colCount, sizeof(colCount));
    SetDimensions(rowCount, colCount);
    
    m_pMatrix = new int[m_valCount];
    
    file.read((char*) m_pMatrix, m_valCount * sizeof(int));
    file.close();
    
#if ENCRYPT_DATA
    EncryptOrDecrypt();
#endif
    
    ConvertToVectors();
}

void MyMatrix::WriteToBinFile(char *fileName)
{
    std::ofstream file;
    
#if ENCRYPT_DATA
    EncryptOrDecrypt();
#endif
    
    file.open(fileName, std::ios::binary);
    file.write((char*) &m_rowCount, sizeof(m_rowCount));
    file.write((char*) &m_colCount, sizeof(m_colCount));
    file.write((char*) m_pMatrix, m_valCount * sizeof(int));
    
    file.close();
}

void MyMatrix::WriteToTextFile(char *fileName)
{
    std::ofstream file;
    
    file.open(fileName);
    
    file << m_rowCount << std::endl;
    file << m_colCount << std::endl;
    
    for (int i = 0; i < m_rowCount; i++)
    {
        for (int j = 0; j < m_colCount; j++)
        {
            file << m_pMatrix[m_colCount * i + j] << " ";
        }
        
        file << std::endl;
    }
    
    file.close();
}

void MyMatrix::CreateWithRandomValues()
{
    m_pMatrix = new int[m_valCount];
    
    for (int i = 0; i < m_rowCount; i++)
    {
        for (int j = 0; j < m_colCount; j++)
        {
            m_pMatrix[m_colCount * i + j] = rand();
        }
    }
    
    ConvertToVectors();
}


void MyMatrix::CreateWithSpecifiedValues(std::string values)
{
    std::stringstream ss(values);
    int val, i = 0;
    
    m_pMatrix = new int[m_valCount];
    
    while (ss >> val)
    {
        if (i >= m_valCount)
        {
            throw std::invalid_argument("Too many matrix values");
        }
        
        m_pMatrix[i++] = val;
        
        if (ss.peek() == ',')
        {
            ss.ignore();
        }
    }
    
    ConvertToVectors();
}

void MyMatrix::CreateWithVector(std::vector<std::vector<int> >& values)
{
    m_vecMatrix = values;
    
    CreateMap();
}


void MyMatrix::EncryptOrDecrypt()
{
    for (int i = 0; i < m_valCount; i++)
    {
        m_pMatrix[i] ^= XOR_MASK;
    }
}

void MyMatrix::ConvertToVectors()
{
    if (m_pMatrix == NULL || m_valCount == 0)
    {
        throw std::runtime_error("Cannot convert null matrix");
    }
    
    m_vecMatrix.resize(m_rowCount);
    
    for (int i = 0; i < m_rowCount; i++)
    {
        m_vecMatrix[i].resize(m_colCount);
        
        for (int j = 0; j < m_colCount; j++)
        {
            m_vecMatrix[i][j] = m_pMatrix[m_colCount * i + j];
        }
    }
    
    CreateMap();
}

void MyMatrix::CreateMap()
{
    if (m_vecMatrix.size() == 0 || m_vecMatrix[0].size() == 0)
    {
        throw std::runtime_error("Empty vector metrix");
    }
    
    std::cout << "Creating map...\n";
    
    m_mapMatrix.resize(m_vecMatrix.size());
    
    for (int i = 0; i < m_vecMatrix.size(); i++)
    {
        std::unordered_map<int,int>& currMap = m_mapMatrix[i];
        
        currMap.reserve(m_vecMatrix[i].size());
        
        for (int j = 0; j < m_vecMatrix[i].size(); j++)
        {
            int currVal = m_vecMatrix[i][j];
            
            if (currMap.find(currVal) == currMap.end())
            {
                currMap[currVal] = 1;
            }
            else
            {
                currMap[currVal] = currMap[currVal] + 1;
            }
        }
    }
    
    std::cout << "Created map\n";
}


void MyMatrix::PrintVectors()
{
    if (m_vecMatrix.size() == 0)
    {
        std::cout << "Empty vector matrix" << std::endl;
    }
    else
    {
        std::cout << "Vector matrix:" << std::endl;
        std::cout << m_vecMatrix.size() << std::endl;
        std::cout << m_vecMatrix[0].size() << std::endl;
        
        for (int i = 0; i < m_vecMatrix.size(); i++)
        {
            for (int j = 0; j < m_vecMatrix[i].size(); j++)
            {
                std::cout << m_vecMatrix[i][j] << " ";
            }
            
            std::cout << std::endl;
        }
    }
}
