//
// Created by rryrr on 4/6/2021.
//

#ifndef NAIVE_BAYES_FOURDIMENSIONAL_VECTOR_H
#define NAIVE_BAYES_FOURDIMENSIONAL_VECTOR_H
#include <vector>
using std::vector;

class FourDimensional_Vector {
public:
    FourDimensional_Vector(size_t row, size_t col, size_t class_num, size_t shade_num, double laplace_smoothing);
    
    double GetValue(size_t row, size_t col, size_t class_label, size_t shade);
    vector<double> GetShades(size_t row, size_t col, size_t class_label);
    void SetValue(size_t row, size_t col, size_t class_label, size_t shade, double val);
    void Print4DVector();
    
private:
    vector<vector<vector<vector<double>>>> data_values_;
    size_t row_size;
    size_t col_size;
    size_t class_size;
    size_t shade_size;
};


#endif //NAIVE_BAYES_FOURDIMENSIONAL_VECTOR_H
