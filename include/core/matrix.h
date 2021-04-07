#include <vector>

using std::vector;

#ifndef NAIVE_BAYES_MATRIX_H
#define NAIVE_BAYES_MATRIX_H

//template <typename ElementType>
class Matrix {
public:
    Matrix();
    Matrix(size_t row_size, size_t col_size);
    void SetValue(size_t row, size_t col, char val);
    char GetValue(size_t row, size_t col);
    void PrintMatrix();
    size_t GetRowSize();
    size_t GetColSize();

private:
    vector<vector<char>> data_values_;
    size_t row_size;
    size_t col_size;
    int class_label;
};


#endif //NAIVE_BAYES_MATRIX_H
