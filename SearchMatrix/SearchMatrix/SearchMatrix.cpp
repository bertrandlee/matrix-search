//
//  main.cpp
//  SearchMatrix
//
//  Created by Bertrand Lee on 21/6/18.
//  Copyright © 2018 Bertrand Lee. All rights reserved.
//

#include <iostream>
#include "MyMatrix.h"

#define E_INVALIDARG 1

void Usage(const char *cmd)
{
    printf("Usage: %s datafile [searchcommands]\n", cmd);
    printf("Eg: %s matrix.dat\n", cmd);
    printf("Eg: %s matrix.dat search.txt\n", cmd);
}


int main(int argc, const char * argv[]) {
    int ret = 0;
    MyMatrix matrix;
    
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
        printf("ReadBin: binFile=%s, outFile=%s\n", fileName, "SearchMatrix.txt");
        matrix.ReadFromBinFile(fileName);
        matrix.WriteToTextFile((char*) "SearchMatrix.txt");
        
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
