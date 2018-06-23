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

#define E_INVALIDARG 1

class MyParser
{
public:
    
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
        
        fstream.open(strCmdFile);
        
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
        std::vector<int> values;
        
        getline(stream, strCmd, ' ');
        
        if (stream.eof())
        {
            std::string errMsg = "Invalid command: \"" + strCmd + "\"";
            throw std::invalid_argument(errMsg);
        }
        
        if (strCmd == "searchSequence")
        {
            ParseCommandValues(strCmd, stream, values);
            PrintParsedCommand(strCmd, values);
        }
        else if (strCmd == "searchUnordered")
        {
            ParseCommandValues(strCmd, stream, values);
            PrintParsedCommand(strCmd, values);
        }
        else if (strCmd == "searchBestMatch")
        {
            ParseCommandValues(strCmd, stream, values);
            PrintParsedCommand(strCmd, values);
        }
        else
        {
            std::string errMsg = "Invalid command: \"" + strCmd + "\"";
            throw std::invalid_argument(errMsg);
        }
    }
};

void Usage(const char *cmd)
{
    printf("Usage: %s datafile [searchcommands]\n", cmd);
    printf("Eg: %s matrix.dat\n", cmd);
    printf("Eg: %s matrix.dat search.txt\n", cmd);
}


int main(int argc, const char * argv[]) {
    int ret = 0;
    MyMatrix matrix;
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
        printf("Reading bin file: %s\n", fileName);
        matrix.ReadFromBinFile(fileName);
        
        // Test std::vector matrix
        printf("Converting vectors\n");
        matrix.ConvertToVectors();
        printf("Converted vectors\n");
        //matrix.PrintVectors();
        
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
