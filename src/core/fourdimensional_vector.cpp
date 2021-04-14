#include "core/fourdimensional_vector.h"
#include <vector>
using std::vector;

FourDimensional_Vector::FourDimensional_Vector(size_t row_num, size_t col_num, size_t class_num, size_t shade_num,
                                               float default_value) : row_size(row_num), col_size(col_num),
                                                                       class_size(class_num), shade_size(shade_num) {
    for (size_t row = 0; row < row_num; row++) {

        vector<vector<vector<float>>> probability_matrix;
        for (size_t col = 0; col < col_num; col++) {

            vector<vector<float>> classes;
            for (size_t class_index = 0; class_index < class_num; class_index++) {

                vector<float> shades;
                for (size_t shade = 0; shade < shade_num; shade++) {
                    shades.push_back(default_value);

                }
                classes.push_back(shades);
            }
            probability_matrix.push_back(classes);
        }
        data_values_.push_back(probability_matrix);
    }
}

float FourDimensional_Vector::GetValue(size_t row, size_t col, size_t class_label, size_t shade) {
    return data_values_[row][col][class_label][shade];
}

void FourDimensional_Vector::SetValue(size_t row, size_t col, size_t class_label, size_t shade, float val) {
    data_values_[row][col][class_label][shade] = val;
}

vector<float> FourDimensional_Vector::GetShades(size_t row, size_t col, size_t class_label) {
    return data_values_[row][col][class_label];
}

size_t FourDimensional_Vector::GetRowSize() {
    return row_size;
}

size_t FourDimensional_Vector::GetColSize() {
    return col_size;
}

size_t FourDimensional_Vector::GetClassSize() {
    return class_size;
}

size_t FourDimensional_Vector::GetShadeSize() {
    return shade_size;
}