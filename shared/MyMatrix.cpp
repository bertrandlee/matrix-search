#include <iostream>
#include <fstream>
#include <sstream>
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
    m_valCount = rowCount * colCount;
    
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
}

void MyMatrix::EncryptOrDecrypt()
{
    for (int i = 0; i < m_valCount; i++)
    {
        m_pMatrix[i] ^= XOR_MASK;
    }
}

