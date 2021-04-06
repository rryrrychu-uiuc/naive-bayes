//
// Created by rryrr on 4/6/2021.
//
#include <iostream>
#include <fstream>
#include <string>
#include "core/image_processor.h"

Image_Processor::Image_Processor(size_t num_rows, size_t num_cols) :
        kNumRows(num_rows), kNumCols(num_cols) {}

vector<Training_Data> Image_Processor::ProcessFile(std::string file_path) {

    vector<Training_Data> labelled_images;
    std::ifstream input_file(file_path);

    if(!input_file.is_open()) {
        throw std::invalid_argument("Invalid Path");
    }

    while (!input_file.eof()) {
        //takes the label number
        std::string line;
        std::getline(input_file, line);
        int number_label = std::stoi(line);

        //builds matrix representing image from the next lines (assumes square)
        Matrix image(kNumRows, kNumCols);
        for (size_t row = 0; row < kNumRows; row++) {
            std::getline(input_file, line);
            for (size_t col = 0; col < kNumCols; col++) {
                image.SetValue(row, col, line[col]);
            }
        }

        labelled_images.push_back(Training_Data(number_label, image));
    }

    input_file.close();
    return labelled_images;
}