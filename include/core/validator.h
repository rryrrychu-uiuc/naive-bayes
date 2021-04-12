#ifndef NAIVE_BAYES_VALIDATOR_H
#define NAIVE_BAYES_VALIDATOR_H

#include "classifier.h"

class Validator {
public:
    Validator(Classifier classifier);
    
    float GetClassifierAccuracy();

    friend std::istream &operator>>(std::istream &is, Validator &target_validator);
    
private:
    Classifier target_classifier_;
    vector<int> classifications_;
    vector<int> labelled_values_;
    
};


#endif //NAIVE_BAYES_VALIDATOR_H
