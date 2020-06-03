#include "matrix.h"

Matrix:: Matrix(int c, int r):m_ColSize(c), m_RowSize(r) {
    m_NumArray = new double*[c];
    for (int i = 0; i < c; ++i) 
        m_NumArray[i] = new double[r];
}
