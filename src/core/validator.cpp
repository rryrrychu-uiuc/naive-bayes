#include <string>
#include "core/validator.h"

Validator::Validator(Classifier classifier): target_classifier_(classifier){}

float Validator::GetClassifierAccuracy() {
    if(classifications_.size() == 0 || labelled_values_.size() == 0) {
        throw std::exception("No test file has been input to the validator to validate classifier");
    }
    
    int num_correct_classified = 0;
    for(size_t index = 0; index < classifications_.size(); index++) {
        if (classifications_[index] == labelled_values_[index]) {
            num_correct_classified++;
        }
    }
    return (float)num_correct_classified/classifications_.size();
}

vector<int> Validator::GetLabelledValues() {
    if(classifications_.size() == 0 || labelled_values_.size() == 0) {
        throw std::exception("No test file has been input to the validator to validate classifier");
    }
    return labelled_values_;
}

vector<int> Validator::GetDeterminedClassifications() {
    if(classifications_.size() == 0 || labelled_values_.size() == 0) {
        throw std::exception("No test file has been input to the validator to validate classifier");
    }
    return classifications_;
}

std::istream &operator>>(std::istream& is, Validator& target_validator) {
    if(is.peek() == std::istream::traits_type::eof() || is.eof()) {
        throw std::exception("Input file invalid");
    }
    
    Classifier target_classifier = target_validator.target_classifier_;
    size_t row_size = target_classifier.GetRowSize();
    size_t col_size = target_classifier.GetColSize();
    
    while (!is.eof()) {
        //takes the label number and stores it in its own vector
        std::string line;
        std::getline(is, line);
        if(line == "") {
            return is;
        }
        target_validator.labelled_values_.push_back(std::stoi(line));
        
        //builds matrix representing image from the next lines (assumes square)
        Matrix image(row_size, col_size);
        for (size_t row = 0; row < row_size; row++) {
            std::getline(is, line);
            for (size_t col = 0; col < col_size; col++) {
                image.SetValue(row, col, line[col]);
            }
        }
        
        //classify the image and store its predicted classification in its own vector
        target_validator.classifications_.push_back(target_classifier.GetPredictedClass(image));
    }

    return is;
}