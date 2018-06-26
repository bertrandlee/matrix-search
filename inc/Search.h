#ifndef _SEARCH_H_
#define _SEARCH_H_

#include <vector>
#include <unordered_map>

typedef enum _SearchType
{
    FindMatchingRows,
    FindBestMatchRow
} SearchType;

class SearchBase
{
public:
    SearchBase() {};
    virtual ~SearchBase() {};
    
    // If m_searchType == FindMatchingRows, set result param to list of matching row indices. Set to empty list if no match.
    // If m_searchType == FindBestMatchRow, set result param to row index with best match. Set to empty list if no match.
    void SearchMatrix(std::vector<std::vector<int> >& matrix, std::vector<int>& sequence, std::vector<int>& result, bool logtime = false, const char* caller = "");
    
protected:
    virtual void Preprocess(std::vector<int>& sequence) {};
    
    // If m_searchType == FindMatchingRows, return 0 if found, -1 if not found
    // If m_searchType == FindBestMatchRow, return count of matching search elements
    virtual int SearchRow(int rowIdx, std::vector<int>& row, std::vector<int>& sequence) = 0;
    
    SearchType m_searchType;
};

class SearchSequenceMapBase : public SearchBase
{
public:
    SearchSequenceMapBase(){};
    virtual ~SearchSequenceMapBase() {};
    
protected:
    void Preprocess(std::vector<int>& sequence);
    
    std::unordered_map<int,int> m_mapSeq;
};


class SearchSequenceNaive : public SearchBase
{
public:
    SearchSequenceNaive()
    {
        m_searchType = FindMatchingRows;
    };
    virtual ~SearchSequenceNaive() {};
    
private:
    int SearchRow(int rowIdx, std::vector<int>& row, std::vector<int>& sequence);
};

class SearchSequenceOptimized : public SearchBase
{
public:
    SearchSequenceOptimized()
    {
        m_searchType = FindMatchingRows;
    };
    virtual ~SearchSequenceOptimized() {};
    
private:
    void Preprocess(std::vector<int>& sequence);
    int SearchRow(int rowIdx, std::vector<int>& row, std::vector<int>& sequence);
    
    std::vector<int> m_vectLPS;
};

class SearchUnorderedNaive : public SearchBase
{
public:
    SearchUnorderedNaive()
    {
        m_searchType = FindMatchingRows;
    };
    virtual ~SearchUnorderedNaive() {};
    
private:
    void Preprocess(std::vector<int>& sequence);
    int SearchRow(int rowIdx, std::vector<int>& row, std::vector<int>& sequence);
    
    std::vector<int> m_sortedSeq;
};

class SearchUnorderedOptimized : public SearchSequenceMapBase
{
public:
    SearchUnorderedOptimized(std::vector<std::unordered_map<int, int> >& mapMatrix)
    {
        m_mapMatrix = mapMatrix;
        m_searchType = FindMatchingRows;
    };
    virtual ~SearchUnorderedOptimized() {};
    
    
private:
    int SearchRow(int rowIdx, std::vector<int>& row, std::vector<int>& sequence);
    
    std::vector<std::unordered_map<int, int> > m_mapMatrix;
};

class SearchBestMatchNaive : public SearchBase
{
public:
    SearchBestMatchNaive()
    {
        m_searchType = FindBestMatchRow;
    };
    virtual ~SearchBestMatchNaive() {};
    
private:
    void Preprocess(std::vector<int>& sequence);
    int SearchRow(int rowIdx, std::vector<int>& row, std::vector<int>& sequence);
    
    std::vector<int> m_sortedSeq;
};

class SearchBestMatchOptimized : public SearchSequenceMapBase
{
public:
    SearchBestMatchOptimized(std::vector<std::unordered_map<int, int> >& mapMatrix)
    {
        m_mapMatrix = mapMatrix;
        m_searchType = FindBestMatchRow;
    };
    virtual ~SearchBestMatchOptimized() {};
    
private:
    int SearchRow(int rowIdx, std::vector<int>& row, std::vector<int>& sequence);
    
    std::vector<std::unordered_map<int, int> > m_mapMatrix;
};



#endif // _SEARCH_H_
