#include <string>
#include "core/image_processor.h"

ImageProcessor::ImageProcessor(size_t num_rows, size_t num_cols) :
        kNumRows(num_rows), kNumCols(num_cols) {}

vector<TrainingData> ImageProcessor::GetLabelledImages() {
    return labelled_images;
}        
        
std::istream &operator>>(std::istream& is, ImageProcessor& processed_images) {
    if(is.peek() == std::istream::traits_type::eof() || is.eof()) {
        throw std::exception();
    }

    while (!is.eof()) {
        //takes the label number
        std::string line;
        std::getline(is, line);
        if(line == "") {
            return is;
        }
        int number_label = std::stoi(line);

        //builds matrix representing image from the next lines (assumes square)
        Matrix image(processed_images.kNumRows, processed_images.kNumCols);
        for (size_t row = 0; row < processed_images.kNumRows; row++) {
            std::getline(is, line);
            for (size_t col = 0; col < processed_images.kNumCols; col++) {
                image.SetValue(row, col, line[col]);
            }
        }
        processed_images.labelled_images.push_back(TrainingData(number_label, image));
    }
    return is;
}
