#include <catch2/catch.hpp>
#include <core/matrix.h>
#include <core/image_processor.h>
#include <fstream>

TEST_CASE("Proper Image Processing") {
    ImageProcessor test_process(5, 5);

    std::ifstream target_file;

    target_file.open("tests/test_data/test_images.txt");
    
    if(target_file.good()) {
        target_file >> test_process;
    } else if(target_file.bad()) {
        throw std::invalid_argument("File doesn't exist");
    }
    
    vector<TrainingData> test_values = test_process.GetLabelledImages();
    REQUIRE(test_values.size() == 8);
    vector<int> values = {6,7,8,7,6,7,8,8};
    int index = 0;
    for(TrainingData labelled_value: test_values) {
        REQUIRE(labelled_value.GetClassLabel() == values[index]);
        index++;
    }
}