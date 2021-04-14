#include <catch2/catch.hpp>
#include <core/matrix.h>
#include <core/image_processor.h>
#include <fstream>

TEST_CASE("Invalid Image Processor File Format") {
    SECTION("File not found") {
        ImageProcessor test_process(5, 5);
        std::ifstream my_file ("tests/test_data/fsdfaf.txt");
        REQUIRE_THROWS(my_file >> test_process);
    }
    SECTION("Empty file") {
        ImageProcessor test_process(5, 5);
        std::ifstream my_file ("tests/test_data/empty_file.txt");
        REQUIRE_THROWS(my_file >> test_process);
    }
}

TEST_CASE("Proper Image Processing") {
    ImageProcessor test_process(5, 5);

    std::ifstream target_file;

    target_file.open("tests/test_data/test_training_images.txt");
    target_file >> test_process;
    
    vector<TrainingData> test_values = test_process.GetLabelledImages();
    REQUIRE(test_values.size() == 15);
    vector<int> values = {1,7,8,7,6,7,8,8,0,2,3,4,5,9,6};
    int index = 0;
    for(TrainingData labelled_value: test_values) {
        REQUIRE(labelled_value.GetClassLabel() == values[index]);
        index++;
    }
}