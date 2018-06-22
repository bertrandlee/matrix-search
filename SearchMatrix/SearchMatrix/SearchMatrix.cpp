//
//  main.cpp
//  SearchMatrix
//
//  Created by Bertrand Lee on 21/6/18.
//  Copyright © 2018 Bertrand Lee. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "MyMatrix.h"

using namespace std;

#define E_INVALIDARG 1

class MyParser
{
public:
    
    void ParseConsole()
    {
        cout << "Enter one of the following commands:" << endl;
        cout << "<searchSequence | searchUnordered | searchBestMatch> <number sequence>" << endl;
        cout << "q (to quit)" << endl;
        cout << "Eg: searchSequence 1 2 3" << endl;
        
        string strCmdLine;
        
        while (true)
        {
            cout << "> ";
            
            getline(cin, strCmdLine);
            
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
                catch (invalid_argument e)
                {
                    printf("ERROR: %s\n", e.what());
                }
            }
        }
    }
    
    void ParseCommandFile(string strCmdFile)
    {
        ifstream fstream;
        string strCmdLine;
        
        fstream.open(strCmdFile);
        
        while (!fstream.eof())
        {
            getline(fstream, strCmdLine);
            
            if (strCmdLine.length() > 0)
            {
                cout << strCmdLine << endl;
                ParseCommand(strCmdLine);
            }
        }
        
        fstream.close();
    }
    
    
private:
    
    void PrintParsedCommand(string& strCmd, vector<int>& values)
    {
        cout << "Parsed: " << strCmd << " ";
        
        for (int i = 0; i < values.size(); i++)
        {
            cout << values[i] << " ";
        }
        
        cout << endl;
    }
    
    void ParseCommandValues(string& strCmd, istringstream& stream, vector<int>& values)
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
            throw invalid_argument("No number sequence specified");
        }
    }
    
    void ParseCommand(string& strCmdLine)
    {
        istringstream stream(strCmdLine);
        string strCmd;
        vector<int> values;
        
        getline(stream, strCmd, ' ');
        
        if (stream.eof())
        {
            string errMsg = "Invalid command: \"" + strCmd + "\"";
            throw invalid_argument(errMsg);
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
            string errMsg = "Invalid command: \"" + strCmd + "\"";
            throw invalid_argument(errMsg);
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
        
        // Test vector matrix
        matrix.ConvertToVectors();
        matrix.PrintVectors();
        
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
