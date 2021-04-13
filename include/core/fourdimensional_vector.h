#pragma once
#ifndef NAIVE_BAYES_FOURDIMENSIONAL_VECTOR_H
#define NAIVE_BAYES_FOURDIMENSIONAL_VECTOR_H

#include <vector>

using std::vector;

class FourDimensional_Vector {
public:
    /**
     * Creates a 4D vector given size of each vector and an initial value
     */
    FourDimensional_Vector(size_t row, size_t col, size_t class_num, size_t shade_num, float default_value);

    /**
     * returns the value at the 4th level vector
     */
    float GetValue(size_t row, size_t col, size_t class_label, size_t shade);

    /**
     * returns all of the values at the 4th level vector
     */
    vector<float> GetShades(size_t row, size_t col, size_t class_label);

    /**
     * set the value at the 4th value vector given index at each vector
     */
    void SetValue(size_t row, size_t col, size_t class_label, size_t shade, float val);
    
    size_t GetRowSize();

    size_t GetColSize();

    size_t GetClassSize();

    size_t GetShadeSize();

private:
    vector<vector<vector<vector<float>>>> data_values_;
    size_t row_size;
    size_t col_size;
    size_t class_size;
    size_t shade_size;
};


#endif //NAIVE_BAYES_FOURDIMENSIONAL_VECTOR_H
