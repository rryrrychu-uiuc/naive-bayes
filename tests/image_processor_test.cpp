#include <catch2/catch.hpp>
#include <core/matrix.h>
#include <core/image_processor.h>

TEST_CASE("Proper Image Processing") {
    Image_Processor test_process(5,5);
    vector<Training_Data> test_values = test_process.ProcessFile("tests/test_data/test_images.txt");
    REQUIRE(test_values.size() == 3);
    vector<int> values = {6,7,8};
    int index = 0;
    for(Training_Data labelled_value: test_values) {
        REQUIRE(labelled_value.GetClassLabel() == values[index]);
        index++;
    }
}