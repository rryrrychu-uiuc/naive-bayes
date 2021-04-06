#ifndef NAIVE_BAYES_TRAINING_DATA_H
#define NAIVE_BAYES_TRAINING_DATA_H

#include "matrix.h"

class Training_Data {
public:
    Training_Data(int label, Matrix image);
    int GetClassLabel();
    Matrix GetFeatureMatrix();
    void Print();

private:
    int class_label;
    Matrix feature_matrix;
};


#endif //NAIVE_BAYES_TRAINING_DATA_H
