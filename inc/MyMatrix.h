#ifndef _MYMATRIX_H_
#define _MYMATRIX_H_

#include <vector>
#include <unordered_map>

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
    void CreateWithVector(std::vector<std::vector<int> >& values);
    void PrintVectors();
    
    inline std::vector<std::vector<int> >& GetVectorMatrix()
    {
        return m_vecMatrix;
    }
    
    inline std::vector<std::unordered_map<int, int> >& GetMap()
    {
        return m_mapMatrix;
    }
    
    
private:
    void EncryptOrDecrypt();
    void CreateMap();
    void ConvertToVectors();
    
    int *m_pMatrix;
    int m_rowCount;
    int m_colCount;
    long long m_valCount;
    std::vector<std::vector<int> > m_vecMatrix;
    std::vector<std::unordered_map<int, int> > m_mapMatrix;
};

#endif // _MYMATRIX_H_

