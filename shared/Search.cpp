#include <ctime>
#include <iostream>
#include <unistd.h>
#include "Search.h"

// SearchBase methods
void SearchBase::SearchMatrix(std::vector<std::vector<int> >& matrix, std::vector<int>& sequence, std::vector<int>& result, bool logtime, const char *caller)
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
    
    Preprocess(sequence);
    
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
        std::cout << caller << ": matrix search time = " << (time_b - time_a) / 1000 << " ms" << std::endl;
    }

}

// SearchSequenceNaive methods
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

// SearchSequenceOptimized methods

// Build KMP LPS array
void SearchSequenceOptimized::Preprocess(std::vector<int>& sequence)
{
    int seqSize = (int) sequence.size(), k;
    
    m_vectLPS.resize(seqSize);
    m_vectLPS[0] = -1;
    
    for (int i = 1; i < seqSize; i++)
    {
        k = m_vectLPS[i - 1];
        
        while (k >= 0)
        {
            if (sequence[k] == sequence[i - 1])
            {
                break;
            }
            else
            {
                k = m_vectLPS[k];
            }
        }
        
        m_vectLPS[i] = k + 1;
    }
}

// Use KMP search algorithm
int SearchSequenceOptimized::SearchRow(std::vector<int>& row, std::vector<int>& sequence)
{
    int seqSize = (int) sequence.size();
    int rowSize = (int) row.size();
    int i = 0; // row index
    int k = 0; // sequence index
    
    while (i < rowSize)
    {
        if (k == -1)
        {
            i++;
            k = 0;
        }
        else if (row[i] == sequence[k])
        {
            i++;
            k++;
            
            if (k == seqSize)
            {
                return 0;
            }
        }
        else
        {
            k = m_vectLPS[k];
        }
    }
    
    return -1;
}

