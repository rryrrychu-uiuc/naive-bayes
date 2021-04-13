#pragma once
#ifndef NAIVE_BAYES_CLASSIFIER_H
#define NAIVE_BAYES_CLASSIFIER_H

#include "naive_bayes_model.h"
#include "matrix.h"

using naivebayes::NaiveBayesModel;

class Classifier {
public:
    
    Classifier(NaiveBayesModel target_model, size_t row_size, size_t col_size);
    int GetPredictedValue(Matrix image);
    
    size_t GetRowSize();
    size_t GetColSize();
    
private:
    const char kDarkPixel = '#';
    const char kShadedPixel = '+';
    const char kUnshadedPixel = ' ';
    const int kShadedValue = 0;
    const int kUnshadedValue = 1;

    NaiveBayesModel trained_model_;
    size_t row_size;
    size_t col_size;

    //calculate the likelihood scores for each class using logarithms to prevent underflow
    vector<float> CalculateLikelihoodScores(Matrix image);
};


#endif //NAIVE_BAYES_CLASSIFIER_H
