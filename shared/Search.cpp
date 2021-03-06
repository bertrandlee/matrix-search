#include <ctime>
#include <iostream>
#include <algorithm>
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
    
    result.clear();
    result.reserve(matrix.size());
    
    clock_t time_a = clock();
    
    Preprocess(sequence);
    
    clock_t time_b = clock();
    
    if (m_searchType == FindMatrix)
    {
        SearchAllRows(sequence, result);
    }
    else if (m_searchType == FindMatchingRows)
    {        
        for (int i = 0; i < matrix.size(); i++)
        {
            int res = SearchRow(i, matrix[i], sequence);
            
            if (res >= 0)
            {
                result.push_back(i);
            }
        }
    }
    else // searchType == FindBestMatchRow
    {
        int maxMatchCount = 0;
        int maxMatchIdx = -1;
        
        for (int i = 0; i < matrix.size(); i++)
        {
            int matchCount = SearchRow(i, matrix[i], sequence);
            
            if (matchCount == sequence.size())
            {
                // Full match found, exit search loop
                maxMatchIdx = i;
                maxMatchCount = matchCount;
                break;
            }
            else if (matchCount > maxMatchCount)
            {
                maxMatchIdx = i;
                maxMatchCount = matchCount;
            }
        }
        
        if (maxMatchIdx >= 0)
        {
            result.push_back(maxMatchIdx);
        }
    }

    clock_t time_c = clock();
    
    if (logtime)
    {
        std::cout << caller << ": Preprocess time = " << (time_b - time_a) << " us, " << "Total matrix search time = " << (time_c - time_a) << " us" << std::endl;
    }

}

// SearchSequenceMapBase methods
void SearchSequenceMapBase::Preprocess(std::vector<int>& sequence)
{
    m_mapSeq.clear();
    m_mapSeq.reserve(sequence.size());
    
    for (int i = 0; i < sequence.size(); i++)
    {
        int currVal = sequence[i];
        
        auto it = m_mapSeq.find(currVal);
        
        if (it == m_mapSeq.end())
        {
            m_mapSeq[currVal] = 1;
        }
        else
        {
            it->second = it->second + 1;
        }
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
            ret = 0;
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
                if (i < sequence.size()-1 &&
                    sequence[i+1] == sequence[i])
                {
                    // Continue search from current point in row if next item in sequence repeats
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

void FindCommonValues(std::unordered_map<int,int>& mapA, std::unordered_map<int,int>& mapB, std::unordered_map<int,int>& result)
{
    for (auto it = mapA.begin(); it != mapA.end(); ++it)
    {
        if (mapB.find(it->first) != mapB.end())
        {
            result[it->first] = 1;
        }
    }
}

void FindAllCommonValues(std::vector<std::unordered_map<int,int>* >& matches, std::vector<int>& result)
{
    std::unordered_map<int,int> curr, res;
    
    if (matches.size() == 0)
        return;
    
    curr = *(matches[0]);
    
    for (int i = 1; i < matches.size(); i++)
    {
        FindCommonValues(curr, *(matches[i]), res);
        curr = res;
        res.clear();
    }
    
    for (auto it = curr.begin(); it != curr.end(); ++it)
    {
        result.push_back(it->first);
    }
}

void SearchUnorderedOptimized::SearchAllRows(std::vector<int>& sequence, std::vector<int>& result)
{
    auto& mapMaster = m_pMatrix->GetMasterMap();
    
    std::unordered_map<int,int>& mapSeq = m_mapSeq;
    
    std::vector<std::unordered_map<int,int>* > matches;
    matches.reserve(sequence.size());
    
    bool allFound = true;;
    
    for ( auto itSeq = mapSeq.begin(); itSeq != mapSeq.end(); ++itSeq)
    {
        int value = itSeq->first;
        int count = itSeq->second;
        
        if (mapMaster.find(value) != mapMaster.end() &&
            mapMaster[value].find(count) != mapMaster[value].end())
        {
            matches.push_back(&(mapMaster[value][count]));
        }
        else
        {
            // Could not find an element in sequence - break out
            allFound = false;
            break;
        }
    }
    
    if (allFound)
    {
        FindAllCommonValues(matches, result);
    }
    
    //std::sort(result.begin(), result.end());
}


// SearchBestMatchNaive methods

void SearchBestMatchNaive::Preprocess(std::vector<int>& sequence)
{
    m_sortedSeq = sequence;
    std::sort(m_sortedSeq.begin(), m_sortedSeq.end());
}

int SearchBestMatchNaive::SearchRow(int rowIdx, std::vector<int>& row, std::vector<int>& sequence)
{
    sequence = m_sortedSeq;
    int matchCount = 0;
    
    for (int i = 0; i < sequence.size(); i++)
    {
        for (int j = 0; j < row.size(); j++)
        {
            if (sequence[i] == row[j])
            {
                matchCount++;
                
                if (i < sequence.size()-1 &&
                    sequence[i+1] == sequence[i])
                {
                    // Continue search from current point in row if next item in sequence repeats
                    i++;
                }
                else
                {
                    // Restart row search with next (different) item in sequence
                    break;
                }
            }
        }
        
        // Advance to last item in repeating sequence (since remaining repeating items were not matched)
        while (i < sequence.size()-1 &&
               sequence[i+1] == sequence[i])
        {
            i++;
        }
    }
    
    return matchCount;
}
    
// SearchBestMatchOptimized methods

int SearchBestMatchOptimized::SearchRow(int rowIdx, std::vector<int>& row, std::vector<int>& sequence)
{
    std::unordered_map<int,int>& mapSeq = m_mapSeq;
    std::vector<std::unordered_map<int, int> >& mapMatrix = m_pMatrix->GetMap();
    int matchCount = 0;
    
    for ( auto itSeq = mapSeq.begin(); itSeq != mapSeq.end(); ++itSeq )
    {
        std::unordered_map<int,int>& rowMap = mapMatrix[rowIdx];
        
        auto itRow = rowMap.find(itSeq->first);
        
        if (itRow != rowMap.end())
        {
            matchCount += std::min(itRow->second, itSeq->second);
        }
    }
    
    return matchCount;
}

