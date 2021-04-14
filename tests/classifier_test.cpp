#include <catch2/catch.hpp>
#include <core/naive_bayes_model.h>
#include <fstream>
#include <core/classifier.h>
#include <iostream>

using naivebayes::NaiveBayesModel;

TEST_CASE("Likelihood Scores Tests") {
    NaiveBayesModel new_model(5,5);
    std::ifstream ("tests/test_data/proper_expected_probability_values.txt") >> new_model;
    Classifier target_classifier(new_model);

    SECTION("Valid Likelihood Scores") {
        Matrix test_matrix(5,5);
        std::ifstream("tests/test_data/valid_test_image.txt") >> test_matrix;
        vector<float> actual_values = target_classifier.CalculateLikelihoodScores(test_matrix);
        vector<float> expected_values = {-17.5144f, -19.5938f,-16.8212f,-15.4349f,-19.5938f,-14.0486f,-12.4383f,-20.2276f,-13.0085f,-17.5144f};
        for(size_t index = 0; index < actual_values.size(); index++) {
            REQUIRE(actual_values[index] == Approx(expected_values[index]));
        }
    }
    
    SECTION("Invalid matrix size") {
        Matrix test_matrix(4,4);
        std::ifstream("tests/test_data/incorrect_size_matrix.txt") >> test_matrix;

        REQUIRE_THROWS(target_classifier.CalculateLikelihoodScores(test_matrix)); 
    }
    
    SECTION("Invalid symbol matrix") {
        Matrix test_matrix(5,5);
        std::ifstream("tests/test_data/invalid_symbol_matrix.txt") >> test_matrix;

        REQUIRE_THROWS(target_classifier.CalculateLikelihoodScores(test_matrix));
    }
}

TEST_CASE("Get Predicted Classification Tests") {
    NaiveBayesModel new_model(5,5);
    std::ifstream ("tests/test_data/proper_expected_probability_values.txt") >> new_model;
    Classifier target_classifier(new_model);

    SECTION("Valid Predicted Classification") {
        Matrix test_matrix(5,5);
        std::ifstream("tests/test_data/valid_test_image.txt") >> test_matrix;
        REQUIRE(target_classifier.GetPredictedClass(test_matrix) == 6);
    }
    
    SECTION("Invalid matrix size") {
        Matrix test_matrix(4,4);
        std::ifstream("tests/test_data/incorrect_size_matrix.txt") >> test_matrix;

        REQUIRE_THROWS(target_classifier.GetPredictedClass(test_matrix));
    }

    SECTION("Invalid symbol matrix") {
        Matrix test_matrix(5,5);
        std::ifstream("tests/test_data/invalid_symbol_matrix.txt") >> test_matrix;

        REQUIRE_THROWS(target_classifier.GetPredictedClass(test_matrix));
    }
}

