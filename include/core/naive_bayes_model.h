#include <vector>
#include "matrix.h"
#include "training_data.h"
#include "fourdimensional_vector.h"

using std::vector;

#ifndef NAIVE_BAYES_NAIVE_BAYES_MODEL_H
#define NAIVE_BAYES_NAIVE_BAYES_MODEL_H
namespace naivebayes {
class Naive_Bayes_Model {
    
    Naive_Bayes_Model(vector<Training_Data> dataset);
    FourDimensional_Vector GetConditionalProbabilities();
    vector<double> GetPriorProbabilities();
    
    
private:
    const int kLaplaceSmoothingValue;
    const int kPossibleClassNum ;
    const int kBlackShadeValue;
    const int kWhiteShadeValue;
    const size_t kRowSize;
    const size_t kColSize;
    int num_training_images_;
    
    //each location in matrix is another 2D matrix
    //Matrix[class_label][shade]
    FourDimensional_Vector conditional_probabilities_;
    vector<double> prior_probabilities_;
    
};
}

#endif //NAIVE_BAYES_NAIVE_BAYES_MODEL_H
