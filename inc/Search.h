#ifndef _SEARCH_H_
#define _SEARCH_H_

#include <vector>
#include <unordered_map>

class SearchBase
{
public:
    SearchBase() {};
    virtual ~SearchBase() {};
    
    void SearchMatrix(std::vector<std::vector<int> >& matrix, std::vector<int>& sequence, std::vector<int>& result, bool logtime = false, const char* caller = "");
    
protected:
    virtual void Preprocess(std::vector<int>& sequence) {};
    virtual int SearchRow(int rowIdx, std::vector<int>& row, std::vector<int>& sequence) = 0;
};

class SearchSequenceNaive : public SearchBase
{
public:
    SearchSequenceNaive() {};
    virtual ~SearchSequenceNaive() {};
    
private:
    int SearchRow(int rowIdx, std::vector<int>& row, std::vector<int>& sequence);
};

class SearchSequenceOptimized : public SearchBase
{
public:
    SearchSequenceOptimized() {};
    virtual ~SearchSequenceOptimized() {};
    
private:
    void Preprocess(std::vector<int>& sequence);
    int SearchRow(int rowIdx, std::vector<int>& row, std::vector<int>& sequence);
    
    std::vector<int> m_vectLPS;
};

class SearchUnorderedNaive : public SearchBase
{
public:
    SearchUnorderedNaive() {};
    virtual ~SearchUnorderedNaive() {};
    
private:
    void Preprocess(std::vector<int>& sequence);
    int SearchRow(int rowIdx, std::vector<int>& row, std::vector<int>& sequence);
    
    std::vector<int> m_sortedSeq;
};

class SearchUnorderedOptimized : public SearchBase
{
public:
    SearchUnorderedOptimized(std::vector<std::unordered_map<int, int> >& mapMatrix)
    {
        m_mapMatrix = mapMatrix;
    };
    virtual ~SearchUnorderedOptimized() {};
    
    
private:
    void Preprocess(std::vector<int>& sequence);
    int SearchRow(int rowIdx, std::vector<int>& row, std::vector<int>& sequence);
    
    std::unordered_map<int,int> m_mapSeq;
    std::vector<std::unordered_map<int, int> > m_mapMatrix;
};



#endif // _SEARCH_H_
