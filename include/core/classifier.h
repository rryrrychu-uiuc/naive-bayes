#pragma once
#ifndef NAIVE_BAYES_CLASSIFIER_H
#define NAIVE_BAYES_CLASSIFIER_H

#include "naive_bayes_model.h"
#include "matrix.h"

using naivebayes::NaiveBayesModel;

class Classifier {
public:
    /**
     * Create a classifier given a certain model
     * @param target_model 
     */
    Classifier(NaiveBayesModel target_model);

    /**
     * Given a matrix representation of an image, classify it as a certain class 
     * @param image the image to classify
     * @return the class the image is classified, throws IllegalArgument if matrix is not the same size as the model
     */
    int GetPredictedClass(Matrix image);

    /**
     * calculate the likelihood scores for each class using logarithms to prevent underflow
     * @param image target to get the likelihood for 
     * @return a vector with likelihoods for each class
     */
    vector<float> CalculateLikelihoodScores(Matrix image);

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
    
    //given a pixel character, get the integer value
    int GetPixelValue(const char pixel);

    //sum up the log of all of the pixel's probabilities for a given image
    float SumAllClassProbabilities(int class_label, Matrix image);
};


#endif //NAIVE_BAYES_CLASSIFIER_H
