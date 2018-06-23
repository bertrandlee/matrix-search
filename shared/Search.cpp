#include <ctime>
#include <iostream>
#include <unistd.h>
#include "Search.h"


void SearchBase::SearchMatrix(std::vector<std::vector<int> >& matrix, std::vector<int>& sequence, std::vector<int>& result, bool logtime)
{
    if (matrix.size() == 0 || matrix[0].size() == 0)
    {
        throw std::invalid_argument("Invalid matrix size");
    }
    
    if (sequence.size() == 0 || sequence.size() > matrix[0].size())
    {
        throw std::invalid_argument("Invalid sequence size");
    }
    
    result.reserve(matrix.size());
    
    clock_t time_a = clock();
    
    for (int i = 0; i < matrix.size(); i++)
    {
        int res = SearchRow(matrix[i], sequence);
        
        if (res >= 0)
        {
            result.push_back(i);
        }
    }

    clock_t time_b = clock();
    
    if (logtime)
    {
        std::cout << "Matrix search time = " << time_b - time_a << " us" << std::endl;
    }

}


int SearchSequenceNaive::SearchRow(std::vector<int>& row, std::vector<int>& sequence)
{
    int rowSize = (int) row.size();
    int seqSize = (int) sequence.size();
    int ret = -1;
    
    for (int i = 0; i < rowSize - seqSize + 1; i++)
    {
        bool found = true;
        
        for (int j = 0; j < seqSize; j++)
        {
            if (sequence[j] != row[i+j])
            {
                found = false;
                break;
            }
        }
        
        if (found)
        {
            ret = i;
            break;
        }
    }
    
    return ret;
}
