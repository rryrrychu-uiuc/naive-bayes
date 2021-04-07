#include "core/training_data.h"
#include <iostream>

Training_Data::Training_Data(int label, Matrix image) : class_label(label), feature_matrix(image){
    
    row_size = feature_matrix.GetRowSize();
    col_size = feature_matrix.GetColSize();
}

int Training_Data::GetClassLabel() {
    return class_label;
}

Matrix Training_Data::GetFeatureMatrix() {
    return feature_matrix;
}

size_t Training_Data::GetRowSize() {
    return row_size;
}

size_t Training_Data::GetColSize() {
    return col_size;
}

void Training_Data::Print() {
    std::cout << class_label << std::endl;
    feature_matrix.PrintMatrix();
}