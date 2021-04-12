#pragma once
#include "core/training_data.h"

TrainingData::TrainingData(int label, Matrix image) : feature_matrix(image), class_label(label){
    
    row_size = feature_matrix.GetRowSize();
    col_size = feature_matrix.GetColSize();
}

int TrainingData::GetClassLabel() {
    return class_label;
}

Matrix TrainingData::GetFeatureMatrix() {
    return feature_matrix;
}

char TrainingData::GetValue(size_t row, size_t col) {
    return feature_matrix.GetValue(row, col);
}

size_t TrainingData::GetRowSize() {
    return row_size;
}

size_t TrainingData::GetColSize() {
    return col_size;
}