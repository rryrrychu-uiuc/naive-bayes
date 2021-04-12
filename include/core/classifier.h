#pragma once
#ifndef NAIVE_BAYES_CLASSIFIER_H
#define NAIVE_BAYES_CLASSIFIER_H

#include "naive_bayes_model.h"
#include "matrix.h"

class Classifier {
public:
    
    Classifier(vector<TrainingData> dataset);
    float GetPredictedValue(Matrix image);
    
private:
    naivebayes::NaiveBayesModel trained_model_;
    const char kDarkPixel = '#';
    const char kShadedPixel = '+';
    const char kUnshadedPixel = ' ';
    const int kShadedValue = 0;
    const int kUnshadedValue = 1;

    //calculate the likelihood scores for each class using logarithms to prevent underflow
    vector<float> CalculateLikelihoodScores(Matrix image);
};


#endif //NAIVE_BAYES_CLASSIFIER_H
