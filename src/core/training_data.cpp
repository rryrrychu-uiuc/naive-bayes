#include "core/training_data.h"
#include <iostream>

Training_Data::Training_Data(int label, Matrix image):class_label(label), feature_matrix(image) {}

int Training_Data::GetClassLabel() {
    return class_label;
}

Matrix Training_Data::GetFeatureMatrix() {
    return feature_matrix;
}

void Training_Data::Print() {
    std::cout << class_label << std::endl;
    feature_matrix.PrintMatrix();
}