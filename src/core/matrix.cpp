#include "core/matrix.h"
#include <iostream>

Matrix::Matrix(size_t row_size, size_t col_size): kRowSize(row_size), kColSize(col_size){

    if(row_size < 0 || col_size < 0) {
        throw std::invalid_argument("Can't have negative row");
    }

    data_values_ = vector<vector<char>>(row_size, vector<char>(col_size));
}

void Matrix::SetValue(size_t row, size_t col, char val) {
    if(row >= kRowSize || col >= kColSize) {
        throw std::invalid_argument("Invalid row or column index");
    }

    data_values_[row][col] = val;
}

char Matrix::GetValue(size_t row, size_t col) {
    if(row >= kRowSize || col >= kColSize) {
        throw std::invalid_argument("Invalid row or column index");
    }

    return data_values_[row][col];
}

size_t Matrix::GetColSize() {
    return kColSize;
}

size_t Matrix::GetRowSize() {
    return kRowSize;
}
