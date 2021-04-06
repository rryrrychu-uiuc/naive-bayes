#include <catch2/catch.hpp>
#include <core/matrix.h>

TEST_CASE("Matrix initialization") {
    SECTION("Defined size matrix") {
        Matrix starting_matrix(12, 12);
        for(size_t row = 0; row < starting_matrix.GetRowSize(); row++) {
            for(size_t col = 0; col < starting_matrix.GetRowSize(); col++) {
                REQUIRE(starting_matrix.GetValue(row, col) ==  ' ');
            }
        }
    }
}

TEST_CASE("SetValue Method") {
    SECTION("Manually changing values") {
        Matrix starting_matrix(3, 3);
        starting_matrix.PrintMatrix();
        starting_matrix.SetValue(0,0,'+');
        starting_matrix.SetValue(0,2,'+');
        starting_matrix.SetValue(1,1,'z');
        starting_matrix.SetValue(2,0,'+');
        starting_matrix.SetValue(2,2,'+');
        starting_matrix.PrintMatrix();
    }
}


