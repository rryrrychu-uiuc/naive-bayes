#ifndef NAIVE_BAYES_IMAGE_PROCESSOR_H
#define NAIVE_BAYES_IMAGE_PROCESSOR_H

#include "matrix.h"
#include "training_data.h"

class Image_Processor {
public:
    /**
     * Process a file with images and labels given the length and row of the image
     */
    Image_Processor(size_t num_rows, size_t num_cols);

    /**
     * Get all of the training images in a vector of an object that stores the image as a matrix and provides a label
     * for the image
     */
    vector<Training_Data> GetLabelledImages();

    /**
     * Override the stream read operator to read images from a file
     */
    friend std::istream &operator>>(std::istream &is, Image_Processor &processed_images);

    size_t GetRows();

    size_t GetCols();

private:
    const size_t kNumRows;
    const size_t kNumCols;
    vector<Training_Data> labelled_images;
};


#endif //NAIVE_BAYES_IMAGE_PROCESSOR_H
