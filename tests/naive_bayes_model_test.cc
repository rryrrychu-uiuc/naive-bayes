#include <catch2/catch.hpp>
#include <core/naive_bayes_model.h>
#include <core/image_processor.h>
#include <fstream>
#include <iostream>

using namespace naivebayes;

TEST_CASE("Proper Model Calculations") {
    Image_Processor test_process(5,5);

    std::ifstream target_file;
    target_file.open("tests/test_data/test_images.txt");
    if(target_file.good()) {
        target_file >> test_process;
    } else if(target_file.bad()) {
        throw std::invalid_argument("File doesn't exist");
    }
    vector<Training_Data> test_values = test_process.GetLabelledImages();
    Naive_Bayes_Model bayes_model(test_values);
    
    SECTION("Test Conditional Probabilities") {
        
    }
    
    SECTION("Test Prior Probabilities") {
        int index = 0;
        vector<double> expected_priors = {0.0555556,0.0555556,0.0555556,0.0555556,0.0555556,0.0555556,0.166667,0.222222,0.222222,0.0555556};
        for(double actual_prior:bayes_model.GetPriorProbabilities()) {
            REQUIRE(expected_priors[index] == Approx(actual_prior));
            index++;
        }
    }
}
