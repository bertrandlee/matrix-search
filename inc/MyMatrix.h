#ifndef _MYMATRIX_H_
#define _MYMATRIX_H_


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
    
private:
    void EncryptOrDecrypt();
    
    int *m_pMatrix;
    int m_rowCount;
    int m_colCount;
    unsigned int m_valCount;
};

#endif // _MYMATRIX_H_

