#pragma once
#ifndef NAIVE_BAYES_VALIDATOR_H
#define NAIVE_BAYES_VALIDATOR_H

#include "classifier.h"

class Validator {
public:
    /**
     * Creates a validator for evaluating the accuracy of a target classifier
     * @param classifier to be validated for accuracy
     */
    Validator(Classifier classifier);
    
    /**
     * validates all of the results of the classifier given a test file of images and labels 
     * @return the number of images classified correctly / total number of images
     */
    float GetClassifierAccuracy();

    /**
     * Get all of the labels in order from a given file
     * @return a vector of all the expected labels
     */
    vector<int> GetLabelledValues();

    /**
    * Get all of the classifications determined by the classifier for the images
    * @return a vector of all the actual image labels
    */
    vector<int> GetDeterminedClassifications();
    
    /**
     * Read a file with labels and images and save all of the classifications of the images 
     */
    friend std::istream &operator>>(std::istream &is, Validator &target_validator);
    
private:
    Classifier target_classifier_;
    vector<int> classifications_;
    vector<int> labelled_values_;
};


#endif //NAIVE_BAYES_VALIDATOR_H
