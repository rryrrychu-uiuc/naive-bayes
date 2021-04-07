//
// Created by rryrr on 4/6/2021.
//

#include "core/matrix.h"
#include <iostream>

//template <typename ElementType>
Matrix::Matrix(size_t row_size, size_t col_size): row_size(row_size), col_size(col_size){

    if(row_size < 0 || col_size < 0) {
        throw std::invalid_argument("Can't have negative row");
    }

    for(size_t rows = 0; rows < row_size; rows++) {
        std::vector<char> row_vector (col_size);
        std::fill(row_vector.begin(),row_vector.begin()+col_size,' ');
        data_values_.push_back(row_vector);
    }
}

//template <typename ElementType>
void Matrix::SetValue(size_t row, size_t col, char val) {
    if(row >= row_size || col >= col_size) {
        throw std::invalid_argument("Invalid row or column index");
    }

    data_values_[row][col] = val;
}

//template <typename ElementType>
char Matrix::GetValue(size_t row, size_t col) {
    if(row >= row_size || col >= col_size) {
        throw std::invalid_argument("Invalid row or column index");
    }

    return data_values_[row][col];
}

//template <typename ElementType>
void Matrix::PrintMatrix() {
    for(vector<char> line: data_values_) {
        for(char value: line) {
            std::cout << value;
        }
        std::cout << std::endl;
    }
}

//template <typename ElementType>
size_t Matrix::GetColSize() {
    return col_size;
}

//template <typename ElementType>
size_t Matrix::GetRowSize() {
    return row_size;
}
