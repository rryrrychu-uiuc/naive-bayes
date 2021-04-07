#ifndef NAIVE_BAYES_IMAGE_PROCESSOR_H
#define NAIVE_BAYES_IMAGE_PROCESSOR_H

#include "matrix.h"
#include "training_data.h"

class Image_Processor {
public:
    Image_Processor(size_t num_rows, size_t num_cols);
    size_t GetRows();
    size_t GetCols();
    vector<Training_Data> GetLabelledImages();
    
    friend std::istream &operator>>(std::istream& is, Image_Processor& processed_images);
    
private:
    const size_t kNumRows;
    const size_t kNumCols;
    vector<Training_Data> labelled_images;
};


#endif //NAIVE_BAYES_IMAGE_PROCESSOR_H
