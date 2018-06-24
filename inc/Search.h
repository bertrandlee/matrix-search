#ifndef _SEARCH_H_
#define _SEARCH_H_

#include <vector>


class SearchBase
{
public:
    SearchBase() {};
    virtual ~SearchBase() {};
    
    void SearchMatrix(std::vector<std::vector<int> >& matrix, std::vector<int>& sequence, std::vector<int>& result, bool logtime = false, const char* caller = "");
    
protected:
    virtual void Preprocess(std::vector<int>& sequence) {};
    virtual int SearchRow(std::vector<int>& row, std::vector<int>& sequence) = 0;
    
};

class SearchSequenceNaive : public SearchBase
{
public:
    SearchSequenceNaive() {};
    virtual ~SearchSequenceNaive() {};
    
private:
    int SearchRow(std::vector<int>& row, std::vector<int>& sequence);
};

class SearchSequenceOptimized : public SearchBase
{
public:
    SearchSequenceOptimized() {};
    virtual ~SearchSequenceOptimized() {};
    
private:
    void Preprocess(std::vector<int>& sequence);
    int SearchRow(std::vector<int>& row, std::vector<int>& sequence);
    
    std::vector<int> m_vectLPS;
};



#endif // _SEARCH_H_
