#include <catch2/catch.hpp>
#include <core/matrix.h>
#include <fstream>
#include <iostream>

TEST_CASE("Matrix initialization") {
    SECTION("Defined size matrix") {
        Matrix starting_matrix(12, 12);
        for(size_t row = 0; row < starting_matrix.GetRowSize(); row++) {
            for(size_t col = 0; col < starting_matrix.GetColSize(); col++) {
                REQUIRE(starting_matrix.GetValue(row, col) ==  0);
            }
        }
    }
}

TEST_CASE("SetValue Method") {
    SECTION("Manually changing values") {
        
        Matrix starting_matrix(3, 3);
        starting_matrix.SetValue(0,0,'+');
        starting_matrix.SetValue(0,2,'+');
        starting_matrix.SetValue(1,1,'z');
        starting_matrix.SetValue(2,0,'+');
        starting_matrix.SetValue(2,2,'+');
        
        REQUIRE(starting_matrix.GetValue(0, 0) == '+');
        REQUIRE(starting_matrix.GetValue(0, 2) == '+');
        REQUIRE(starting_matrix.GetValue(1, 1) == 'z');
        REQUIRE(starting_matrix.GetValue(2, 0) == '+');
        REQUIRE(starting_matrix.GetValue(2, 2) == '+');
    }
}

TEST_CASE("Matrix Invalid File Input") {
    SECTION("File not found") {
        Matrix test_matrix(5, 5);
        std::ifstream my_file ("tests/test_data/fsdfaf.txt");
        REQUIRE_THROWS(my_file >> test_matrix);
    }
    
    SECTION("Empty file") {
        Matrix test_matrix(5, 5);
        std::ifstream my_file ("tests/test_data/empty_file.txt");
        REQUIRE_THROWS(my_file >> test_matrix);
    }
    
    SECTION("File matrix too big") {
        Matrix test_matrix(5, 5);
        std::ifstream my_file ("tests/test_data/test_matrix_input.txt");
        REQUIRE_THROWS(my_file >> test_matrix);
    }
    
    SECTION("File matrix too small") {
        Matrix test_matrix(3, 3);
        std::ifstream my_file ("tests/test_data/test_matrix_input.txt");
        REQUIRE_THROWS(my_file >> test_matrix);
    }
}

TEST_CASE("Matrix Valid File Input") {
    Matrix test_matrix(5, 4);
    std::ifstream my_file ("tests/test_data/test_matrix_input.txt");
    
    my_file >> test_matrix;
    vector<char> test_value = {'1','2','3','4'};
    
    for(size_t row = 0; row < test_matrix.GetRowSize(); row++) {
        for(size_t col = 0; col < test_matrix.GetColSize(); col++) {
            REQUIRE(test_matrix.GetValue(row, col) == test_value[col]);
        } 
    }
}

