//
// Created by rryrr on 4/6/2021.
//

#include "core/fourdimensional_vector.h"
#include <vector>

using std::vector;


FourDimensional_Vector::FourDimensional_Vector(size_t row_num, size_t col_num, size_t class_num, size_t shade_num,
                                                 double default_value) {

    for (size_t row = 0; row < row_num; row++) {
        
        vector<vector<vector<double>>> probability_matrix;
        for (size_t col = 0; col < col_num; col++) {
            
            vector<vector<double>> classes;
            for(size_t class_index = 0; class_index < class_num; class_index++) {
                
                vector<double> shades;
                for (size_t i = 0; i < shade_num; i++) {
                    shades.push_back(default_value);
                    
                }
                classes.push_back(shades);
            }
            probability_matrix.push_back(classes);
        }
        data_values_.push_back(probability_matrix);
    }
}

double FourDimensional_Vector::GetValue(size_t row, size_t col, size_t class_label, size_t shade) {
    return data_values_[row][col][class_label][shade];
}

void FourDimensional_Vector::SetValue(size_t row, size_t col, size_t class_label, size_t shade, double val) {
    data_values_[row][col][class_label][shade] = val;
}

vector<double> FourDimensional_Vector::GetShades(size_t row, size_t col, size_t class_label) {
    return data_values_[row][col][class_label];
}