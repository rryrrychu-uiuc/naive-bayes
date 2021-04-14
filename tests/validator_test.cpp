#include <catch2/catch.hpp>
#include <core/naive_bayes_model.h>
#include <core/classifier.h>
#include <core/validator.h>
#include <fstream>
#include <iostream>

using naivebayes::NaiveBayesModel;


TEST_CASE("Invalid Validator File") { 
    NaiveBayesModel test_model(5,5);
    std::ifstream target_file;
    target_file.open("tests/test_data/proper_expected_probability_values.txt");
    target_file >> test_model;
    Classifier test_classifier(test_model);

    SECTION("File empty") {
        Validator test_validator(test_classifier);
        std::ifstream target_validator_file;
        target_validator_file.open("tests/test_data/empty_file.txt");
        REQUIRE_THROWS(target_validator_file >> test_validator);
    }
    
    SECTION("File does not exist") {
        Validator test_validator(test_classifier);
        std::ifstream target_validator_file;
        target_validator_file.open("tests/test_data/fasdfasdf.txt");
        REQUIRE_THROWS(target_validator_file >> test_validator);
    }
    
    SECTION("File format invalid") {
        Validator test_validator(test_classifier);
        std::ifstream target_validator_file;
        target_validator_file.open("tests/test_data/proper_expected_probability_values.txt");
        REQUIRE_THROWS(target_validator_file >> test_validator);
    }
}

TEST_CASE("No test file ran on validator") {
    NaiveBayesModel test_model(5,5);
    std::ifstream target_file;
    target_file.open("tests/test_data/proper_expected_probability_values.txt");
    target_file >> test_model;
    Classifier test_classifier(test_model);
    Validator test_validator(test_classifier);
    
    SECTION("GetClassifierAccuracy doesn't run when no test file run"){
        REQUIRE_THROWS(test_validator.GetClassifierAccuracy());
    }
    
    SECTION("GetLabelledValues doesn't run when no test file run"){
        REQUIRE_THROWS(test_validator.GetLabelledValues());
    }
    
    SECTION("GetDeterminedClassifications doesn't run when no test file run"){
        REQUIRE_THROWS(test_validator.GetDeterminedClassifications());
    }
}

TEST_CASE("Valid method operation") {
    NaiveBayesModel test_model(5,5);
    std::ifstream target_file;
    target_file.open("tests/test_data/proper_expected_probability_values.txt");
    target_file >> test_model;
    Classifier test_classifier(test_model);
    
    Validator test_validator(test_classifier);
    std::ifstream file_to_classify;
    file_to_classify.open("tests/test_data/test_test_images.txt");
    file_to_classify >> test_validator;
    
    SECTION("GetClassification correct values") {
        vector<int> expected_classifications = {0,1,1,8,4,6,6,7,8,9};
        vector<int> actual_classifications = test_validator.GetDeterminedClassifications();
        for(size_t index = 0; index < actual_classifications.size(); index++) {
            REQUIRE(actual_classifications[index] == expected_classifications[index]);
        }
    }
    
    SECTION("GetLabelledValues correct values") {
        vector<int> labelled_classes = test_validator.GetLabelledValues();
        int class_label = 0;
        for(size_t index = 0; index < labelled_classes.size(); index++) {
            REQUIRE(labelled_classes[index] == class_label);
            class_label++;
        }
    }
    
    SECTION("GetClassifierAccuracy correct values (sanity check)") {
        REQUIRE(test_validator.GetClassifierAccuracy() == Approx(0.7));
    }
}