//
//  main.cpp
//  SearchMatrix
//
//  Created by Bertrand Lee on 21/6/18.
//  Copyright © 2018 Bertrand Lee. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "MyMatrix.h"
#include "Search.h"

#define E_INVALIDARG 1


class MyParser
{
public:
    MyParser()
    {
        m_pSearchSequence = NULL;
        m_pSearchUnordered = NULL;
        m_pSearchBestMatch = NULL;
    };
    
    virtual ~MyParser()
    {
        if (m_pSearchSequence) delete m_pSearchSequence;
        if (m_pSearchUnordered) delete m_pSearchUnordered;
        if (m_pSearchBestMatch) delete m_pSearchBestMatch;
    };
    
    void Initialize(char* matrixFile)
    {
        printf("Reading bin file: %s\n", matrixFile);
        m_matrix.ReadFromBinFile(matrixFile);
        
        m_pSearchSequence = new SearchSequenceOptimized();
        m_pSearchUnordered = new SearchUnorderedOptimized(&m_matrix);
        m_pSearchBestMatch = new SearchBestMatchOptimized(&m_matrix);
    }
    
    void ParseConsole()
    {
        std::cout << "Enter one of the following commands:" << std::endl;
        std::cout << "<searchSequence | searchUnordered | searchBestMatch> <number sequence>" << std::endl;
        std::cout << "q (to quit)" << std::endl;
        std::cout << "Eg: searchSequence 1 2 3" << std::endl;
        
        std::string strCmdLine;
        
        while (true)
        {
            std::cout << "> ";
            
            getline(std::cin, strCmdLine);
            
            if (strCmdLine == "q")
            {
                break;
            }
            else
            {
                try
                {
                    ParseCommand(strCmdLine);
                }
                catch (std::invalid_argument e)
                {
                    printf("ERROR: %s\n", e.what());
                }
            }
        }
    }
    
    void ParseCommandFile(std::string strCmdFile)
    {
        std::ifstream fstream;
        std::string strCmdLine;
        
        fstream.open(strCmdFile.c_str());
        
        while (!fstream.eof())
        {
            getline(fstream, strCmdLine);
            
            if (strCmdLine.length() > 0)
            {
                std::cout << strCmdLine << std::endl;
                ParseCommand(strCmdLine);
            }
        }
        
        fstream.close();
    }
    
    
private:
    
    void PrintResult(std::vector<int>& result)
    {
        std::cout << "Results(s):\n";
        
        if (result.size() == 0)
        {
            std::cout << "None\n";
        }
        else
        {
            for (int i = 0; i < result.size(); i++)
            {
                std::cout << result[i] << std::endl;
            }
        }
    }
    
    void PrintParsedCommand(std::string& strCmd, std::vector<int>& values)
    {
        std::cout << "Parsed: " << strCmd << " ";
        
        for (int i = 0; i < values.size(); i++)
        {
            std::cout << values[i] << " ";
        }
        
        std::cout << std::endl;
    }
    
    void ParseCommandValues(std::string& strCmd, std::istringstream& stream, std::vector<int>& values)
    {
        int val;
        
        while (!stream.eof())
        {
            while (stream.peek() == ' ')
            {
                stream.ignore();
            }
            
            if (stream >> val)
            {
                values.push_back(val);
            }
            
            while (stream.peek() == ' ')
            {
                stream.ignore();
            }
        }
        
        if (values.size() == 0)
        {
            throw std::invalid_argument("No number sequence specified");
        }
    }
    
    void ParseCommand(std::string& strCmdLine)
    {
        std::istringstream stream(strCmdLine);
        std::string strCmd;
        std::vector<int> sequence, result;
        
        getline(stream, strCmd, ' ');
        
        if (stream.eof())
        {
            std::string errMsg = "Invalid command: \"" + strCmd + "\"";
            throw std::invalid_argument(errMsg);
        }
        
        if (strCmd == "searchSequence")
        {
            ParseCommandValues(strCmd, stream, sequence);
            //PrintParsedCommand(strCmd, sequence);
            m_pSearchSequence->SearchMatrix(m_matrix.GetVectorMatrix(), sequence, result);
            PrintResult(result);
        }
        else if (strCmd == "searchUnordered")
        {
            ParseCommandValues(strCmd, stream, sequence);
            //PrintParsedCommand(strCmd, sequence);
            m_pSearchUnordered->SearchMatrix(m_matrix.GetVectorMatrix(), sequence, result);
            PrintResult(result);
        }
        else if (strCmd == "searchBestMatch")
        {
            ParseCommandValues(strCmd, stream, sequence);
            //PrintParsedCommand(strCmd, sequence);
            m_pSearchBestMatch->SearchMatrix(m_matrix.GetVectorMatrix(), sequence, result);
            PrintResult(result);
        }
        else
        {
            std::string errMsg = "Invalid command: \"" + strCmd + "\"";
            throw std::invalid_argument(errMsg);
        }
    }
    
private:
    MyMatrix m_matrix;
    SearchSequenceOptimized *m_pSearchSequence;
    SearchUnorderedOptimized *m_pSearchUnordered;
    SearchBestMatchOptimized *m_pSearchBestMatch;
};

void Usage(const char *cmd)
{
    printf("Usage: %s datafile [searchcommands]\n", cmd);
    printf("Eg: %s matrix.dat\n", cmd);
    printf("Eg: %s matrix.dat search.txt\n", cmd);
}


int main(int argc, const char * argv[]) {
    int ret = 0;
    MyParser parser;
    
    if (argc < 2)
    {
        Usage(argv[0]);
        ret = E_INVALIDARG;
        goto cleanup;
    }
    
    try
    {
        // Read from bin file
        char *fileName = (char *) argv[1];
        parser.Initialize(fileName);
        
        if (argc == 2)
        {
            parser.ParseConsole();
        }
        else
        {
            parser.ParseCommandFile(argv[2]);
        }
        
    }
    catch (std::invalid_argument e) {
        printf("ERROR: %s\n", e.what());
    }
    catch (std::exception e) {
        printf("ERROR: %s\n", e.what());
    }
    
    
cleanup:
    return ret;
}
