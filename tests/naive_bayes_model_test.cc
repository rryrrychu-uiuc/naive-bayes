#include <catch2/catch.hpp>
#include <core/naive_bayes_model.h>
#include <core/image_processor.h>
#include <fstream>
#include <iostream>

using namespace naivebayes;

TEST_CASE("Load model from file") {

    SECTION("File not found") {
        size_t test_size = 5;
        NaiveBayesModel new_model(test_size,test_size);
        std::ifstream my_file ("tests/test_data/fsdfaf.txt");
        REQUIRE_THROWS(my_file >> new_model);
    }
    SECTION("Empty file") {
        size_t test_size = 5;
        NaiveBayesModel new_model(test_size,test_size);
        std::ifstream my_file ("tests/test_data/empty_file.txt");
        REQUIRE_THROWS(my_file >> new_model);
    }
    
    SECTION("Proper model loading") {
        size_t test_size = 5;
        NaiveBayesModel new_model(test_size,test_size);

        std::ifstream my_file ("tests/test_data/test_load_file.txt");
        my_file >> new_model;

        float val = (float)0.1;
        for(size_t class_num = 0; class_num <= 9; class_num++) {
            REQUIRE(new_model.GetPriorProbability(class_num) == Approx(val));
            val += (float)0.1;
        }

        for (size_t row = 0; row < test_size; row++) {
            for (size_t col = 0; col < test_size; col++) {
                for (size_t class_index = 0; class_index < 10; class_index++) {
                    for (size_t shade = 0; shade < 2; shade++) {
                        REQUIRE(new_model.GetConditionalProbability(row, col, class_index, shade) == Approx(0.2));
                    }
                    std::cout << std::endl;
                }
            }
        }
    }
}

TEST_CASE("Save model to file") {

    size_t test_size = 5;
    NaiveBayesModel new_model(test_size,test_size);

    for(size_t class_num = 0; class_num <= 9; class_num++) {
        new_model.AddPriorValue((float)0.9);
    }
    
    for (size_t row = 0; row < test_size; row++) {
        for (size_t col = 0; col < test_size; col++) {
            for (size_t class_index = 0; class_index < 10; class_index++) {
                for (size_t shade = 0; shade < 2; shade++) {
                    new_model.SetProbabilityValue(row, col, class_index, shade, (float)0.3);
                }
            }
        }
    }
    
    std::ofstream saved_model;
    saved_model.open ("tests/test_data/test_save_file.txt");
    saved_model << new_model;
    saved_model.close();

    std::ifstream my_file ("tests/test_data/test_save_file.txt");
    my_file >> new_model;

    for(size_t class_num = 0; class_num <= 9; class_num++) {
        REQUIRE(new_model.GetPriorProbability(class_num) == Approx(0.9));
    }
    
    for (size_t row = 0; row < test_size; row++) {
        for (size_t col = 0; col < test_size; col++) {
            for (size_t class_index = 0; class_index < 10; class_index++) {
                for (size_t shade = 0; shade < 2; shade++) {
                    REQUIRE(new_model.GetConditionalProbability(row, col, class_index, shade) == Approx(0.3));
                }
            }
        }
    }
}

TEST_CASE("Proper Model Calculations") {
    ImageProcessor test_process(5, 5);

    std::ifstream target_file;
    target_file.open("tests/test_data/test_training_images.txt");
    target_file >> test_process;
    vector<TrainingData> test_values = test_process.GetLabelledImages();
    NaiveBayesModel bayes_model(test_values);

    SECTION("Test Conditional Probabilities") {
        size_t test_size = 5;
        NaiveBayesModel new_model(test_size,test_size);

        std::ifstream my_file ("tests/test_data/proper_expected_probability_values.txt");
        my_file >> new_model;

        for (size_t row = 0; row < test_size; row++) {
            for (size_t col = 0; col < test_size; col++) {
                for (size_t class_index = 0; class_index < 10; class_index++) {
                    for (size_t shade = 0; shade < 2; shade++) {
                        float expected = new_model.GetConditionalProbability(row, col, class_index, shade);
                        float actual = bayes_model.GetConditionalProbability(row, col, class_index, shade);
                        REQUIRE(expected == Approx(actual));
                    }
                    std::cout << std::endl;
                }
            }
        }
    }

    SECTION("Test Prior Probabilities") {
        int index = 0;
        vector<double> expected_priors = {0.08,0.08,0.08,0.08,0.08,0.08,0.12,0.16,0.16,0.08};
        for (double actual_prior:bayes_model.GetPriorProbabilities()) {
            REQUIRE(expected_priors[index] == Approx(actual_prior));
            index++;
        }
    }

}
