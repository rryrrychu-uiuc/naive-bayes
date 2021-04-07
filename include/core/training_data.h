#ifndef NAIVE_BAYES_TRAINING_DATA_H
#define NAIVE_BAYES_TRAINING_DATA_H

#include "matrix.h"

class Training_Data {
public:
    Training_Data(int label, Matrix image);
    int GetClassLabel();
    Matrix GetFeatureMatrix();
    size_t GetRowSize(); 
    size_t GetColSize();
    void Print();

private:
    int class_label;
    size_t row_size;
    size_t col_size;
    Matrix feature_matrix;
};


#endif //NAIVE_BAYES_TRAINING_DATA_H
