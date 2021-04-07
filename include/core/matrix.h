#include <vector>
using std::vector;

#ifndef NAIVE_BAYES_MATRIX_H
#define NAIVE_BAYES_MATRIX_H

class Matrix {
public:
    /**
     * Create an empty matrix or 2D vector
     */
    Matrix();

    /**
    * Create a matrix with set row and col size
    */
    Matrix(size_t row_size, size_t col_size);
    
    void SetValue(size_t row, size_t col, char val);
    
    char GetValue(size_t row, size_t col);
    
    void PrintMatrix();
    
    size_t GetRowSize();
    
    size_t GetColSize();

private:
    vector<vector<char>> data_values_;
    const size_t row_size;
    const size_t col_size;
};


#endif //NAIVE_BAYES_MATRIX_H
