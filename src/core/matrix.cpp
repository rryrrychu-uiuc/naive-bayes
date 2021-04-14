#include "core/matrix.h"
#include <iostream>
#include <string>

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

char Matrix::GetValue(size_t row, size_t col) const {
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

std::istream &operator>>(std::istream &is, Matrix &target_matrix) {
    if(is.peek() == std::istream::traits_type::eof() || is.eof()) {
        throw std::exception();
    }
    
    //gets the sizes from first line of file
    std::string line;
    std::getline(is, line);
    
    if(line.size() != target_matrix.GetColSize()) {
        throw std::invalid_argument("File not correct size");
    }

    for(size_t row = 0; row < target_matrix.GetRowSize(); row++) {
        for(size_t col = 0; col < target_matrix.GetColSize(); col++) {
            target_matrix.data_values_[row][col] = line.at(col);
        }
        std::getline(is, line);
    }
    return is;
}