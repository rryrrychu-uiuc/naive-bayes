#ifndef NAIVE_BAYES_IMAGE_PROCESSOR_H
#define NAIVE_BAYES_IMAGE_PROCESSOR_H

#include "matrix.h"
#include "training_data.h"

class Image_Processor {
public:
    Image_Processor(size_t num_rows, size_t num_cols);
    vector<Training_Data> ProcessFile(std::string file_path);
    
private:
    const size_t kNumRows;
    const size_t kNumCols;
};


#endif //NAIVE_BAYES_IMAGE_PROCESSOR_H
