#pragma once
#ifndef NAIVE_BAYES_TRAINING_DATA_H
#define NAIVE_BAYES_TRAINING_DATA_H

#include "matrix.h"

class TrainingData {
public:
    TrainingData(int label, Matrix image);
    
    int GetClassLabel();
    
    Matrix GetFeatureMatrix();
    
    char GetValue(size_t row, size_t col);
    
    size_t GetRowSize(); 
    
    size_t GetColSize();

private:
    int class_label;
    size_t row_size;
    size_t col_size;
    Matrix feature_matrix;
};

#endif //NAIVE_BAYES_TRAINING_DATA_H
