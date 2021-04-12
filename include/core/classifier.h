#pragma once
#ifndef NAIVE_BAYES_CLASSIFIER_H
#define NAIVE_BAYES_CLASSIFIER_H

#include "naive_bayes_model.h"
#include "matrix.h"

class Classifier {
public:
    
    Classifier(vector<TrainingData> dataset, size_t row_size, size_t col_size);
    float GetPredictedValue(Matrix image);
    
    size_t GetRowSize();
    size_t GetColSize();
    
private:
    const char kDarkPixel = '#';
    const char kShadedPixel = '+';
    const char kUnshadedPixel = ' ';
    const int kShadedValue = 0;
    const int kUnshadedValue = 1;

    naivebayes::NaiveBayesModel trained_model_;
    size_t row_size;
    size_t col_size;

    //calculate the likelihood scores for each class using logarithms to prevent underflow
    vector<float> CalculateLikelihoodScores(Matrix image);
};


#endif //NAIVE_BAYES_CLASSIFIER_H
