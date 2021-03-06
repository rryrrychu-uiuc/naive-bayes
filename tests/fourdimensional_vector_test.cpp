#include <catch2/catch.hpp>
#include <iostream>
#include "core/fourdimensional_vector.h"

TEST_CASE("Initialize fourdimensional vector"){
    FourDimensional_Vector small_picture(3,3,10,2,1);
    
    for(size_t i = 0; i < 3; i++) {
        for(size_t j = 0; j < 3; j++) {
            for(size_t k = 0; k < 10; k++) {
                for(size_t l = 0; l < 2; l++) {
                    REQUIRE(small_picture.GetValue(i,j,k,l) == 1);
                }
            }
        }
    }
}
