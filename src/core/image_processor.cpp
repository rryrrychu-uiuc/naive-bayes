#include <fstream>
#include <string>
#include "core/image_processor.h"
#include "core/matrix.h"

Image_Processor::Image_Processor(size_t num_rows, size_t num_cols) :
        kNumRows(num_rows), kNumCols(num_cols) {}

vector<Training_Data> Image_Processor::GetLabelledImages() {
    return labelled_images;
}        
        
std::istream &operator>>(std::istream& is, Image_Processor& processed_images) {

    while (!is.eof()) {
        //takes the label number
        std::string line;
        std::getline(is, line);
        int number_label = std::stoi(line);

        //builds matrix representing image from the next lines (assumes square)
        Matrix image(processed_images.kNumRows, processed_images.kNumCols);
        for (size_t row = 0; row < processed_images.kNumRows; row++) {
            std::getline(is, line);
            for (size_t col = 0; col < processed_images.kNumCols; col++) {
                image.SetValue(row, col, line[col]);
            }
        }

        processed_images.labelled_images.push_back(Training_Data(number_label, image));
    }

    return is;
}
