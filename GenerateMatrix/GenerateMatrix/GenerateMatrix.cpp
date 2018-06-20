//
//  main.cpp
//  GenerateMatrix
//
//  Created by Bertrand Lee on 19/6/18.
//  Copyright © 2018 Bertrand Lee. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "../../inc/MyMatrix.h"

#define E_INVALIDARG 1


void Usage(const char *cmd)
{
    printf("Usage: %s filename row_count column_count [values]\n", cmd);
    printf("Eg: %s matrix.dat 2 3\n", cmd);
    printf("Eg: %s matrix.dat 2 3 1,2,3,4,5,6\n", cmd);
    printf("Eg: %s -readbin matrix.dat output.txt\n", cmd);
}

int main(int argc, const char * argv[]) {
    int ret = 0;
    char *fileName;
    int rowCount, colCount;
    MyMatrix matrix;
    
    if (argc < 4)
    {
        Usage(argv[0]);
        ret = E_INVALIDARG;
        goto cleanup;
    }
    
    try
    {
        if (strcmp(argv[1], "-readbin") == 0)
        {
            // Read from bin file
            char *fileName = (char *) argv[2];
            char *outFile = (char *) argv[3];
            printf("ReadBin: binFile=%s, outFile=%s\n", fileName, outFile);
            matrix.ReadFromBinFile(fileName);
            matrix.WriteToTextFile((char*) outFile);
        }
        else
        {
            // Generate bin file
            
            fileName = (char *) argv[1];
            
            rowCount = atoi(argv[2]);
            colCount = atoi(argv[3]);
            matrix.SetDimensions(rowCount, colCount);
            
            if (argc == 4)
            {
                printf("CreateWithRandomValues: fileName=%s, rowCount=%d, colCount=%d\n", fileName, rowCount, colCount);
                matrix.CreateWithRandomValues();
                
            }
            else
            {
                char * vals = (char*) argv[4];
                printf("CreateSpecifiedMatrix: fileName=%s, rowCount=%d, colCount=%d, vals=%s\n", fileName, rowCount, colCount, vals);
                matrix.CreateWithSpecifiedValues(vals);
            }
            
            matrix.WriteToBinFile(fileName);
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
