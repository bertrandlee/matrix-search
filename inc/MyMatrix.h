#ifndef _MYMATRIX_H_
#define _MYMATRIX_H_

#include <vector>

class MyMatrix
{
public:
    MyMatrix();
    ~MyMatrix();
    
    void SetDimensions(int rowCount, int colCount);
    void ReadFromBinFile(char *fileName);
    void WriteToBinFile(char *fileName);
    void WriteToTextFile(char *fileName);
    void CreateWithRandomValues();
    void CreateWithSpecifiedValues(std::string values);
    void ConvertToVectors();
    void PrintVectors();
    
    inline std::vector<std::vector<int> >& GetVectorMatrix()
    {
        return m_vecMatrix;
    }
    
    inline std::vector<std::vector<int> >& GetSortedMatrix()
    {
        return m_sortedMatrix;
    }
    
    
private:
    void EncryptOrDecrypt();
    void CreateSortedMatrix();
    
    int *m_pMatrix;
    int m_rowCount;
    int m_colCount;
    long long m_valCount;
    std::vector<std::vector<int> > m_vecMatrix;
    std::vector<std::vector<int> > m_sortedMatrix;
};

#endif // _MYMATRIX_H_

