#ifndef _MATRIX_H_
#define _MATRIX_H_
//start
class Matrix {
public:
    Matrix(int c, int r);
    Matrix(const Matrix& m);
    ~Matrix();
    double& operator()(int i, int j);
    double operator()(int i, int j) const;
    Matrix& operator=(const Matrix& m);
    Matrix& operator+=(Matrix& m);
private:
    int m_ColSize, m_RowSize;
    double  **m_NumArray;
};
//end
#endif

