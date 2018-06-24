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
        int res = SearchRow(i, matrix[i], sequence);
        
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
int SearchSequenceNaive::SearchRow(int rowIdx, std::vector<int>& row, std::vector<int>& sequence)
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
int SearchSequenceOptimized::SearchRow(int rowIdx, std::vector<int>& row, std::vector<int>& sequence)
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

// SearchUnorderedNaive methods

void SearchUnorderedNaive::Preprocess(std::vector<int>& sequence)
{
    m_sortedSeq = sequence;
    std::sort(m_sortedSeq.begin(), m_sortedSeq.end());
}

int SearchUnorderedNaive::SearchRow(int rowIdx, std::vector<int>& row, std::vector<int>& sequence)
{
    sequence = m_sortedSeq;
    bool found = false;
    
    for (int i = 0; i < sequence.size(); i++)
    {
        found = false;
        
        for (int j = 0; j < row.size(); j++)
        {
            if (sequence[i] == row[j])
            {
                // Continue search from current point if there are repeating chars in sequence
                if (i < sequence.size()-1 &&
                    sequence[i+1] == sequence[i])
                {
                    i++;
                }
                else
                {
                    found = true;
                    break;
                }
            }
        }
        
        if (!found)
        {
            break;
        }
    }
    
    return found ? 0 : -1;
}

// SearchUnorderedOptimized methods

void SearchUnorderedOptimized::Preprocess(std::vector<int>& sequence)
{
    for (int i = 0; i < sequence.size(); i++)
    {
        int currVal = sequence[i];
        
        if (m_mapSeq.find(currVal) == m_mapSeq.end())
        {
            m_mapSeq[currVal] = 1;
        }
        else
        {
            m_mapSeq[currVal] = m_mapSeq[currVal] + 1;
        }
    }
}

int SearchUnorderedOptimized::SearchRow(int rowIdx, std::vector<int>& row, std::vector<int>& sequence)
{
    std::unordered_map<int,int> mapSeq = m_mapSeq;
    bool found = true;
    
    for ( auto it = mapSeq.begin(); it != mapSeq.end(); ++it )
    {
        std::unordered_map<int,int>& rowMap = m_mapMatrix[rowIdx];
        
        if (rowMap.find(it->first) == rowMap.end() ||
            rowMap[it->first] < it->second)
        {
            found = false;
            break;
        }
    }
    
    return found ? 0 : -1;
}

