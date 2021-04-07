#include "core/naive_bayes_model.h"

const int kNumShades = 2;
namespace naivebayes {
Naive_Bayes_Model::Naive_Bayes_Model(vector<Training_Data> dataset) :
        num_training_images_(dataset.size()),
        kRowSize(dataset[0].GetRowSize()),
        kColSize(dataset[0].GetColSize()),
        kBlackShadeValue(0),
        kWhiteShadeValue(1),
        kLaplaceSmoothingValue(1),
        kPossibleClassNum(10),
        conditional_probabilities_(kRowSize, kColSize, kPossibleClassNum, 2, kLaplaceSmoothingValue){
    
    vector<int> class_counts(kPossibleClassNum);

    //determine the counts for the shades from the training data
    for (Training_Data data_value : dataset) {

        //counts number of each class in training data
        int class_labels = data_value.GetClassLabel();
        class_counts[class_labels]++;

        //count the shades for each of the classes on each index in the matrix
        for (size_t row = 0; row < data_value.GetFeatureMatrix().GetRowSize(); row++) {
            for (size_t col = 0; col < data_value.GetFeatureMatrix().GetColSize(); col++) {
                vector<double> shade_counts = conditional_probabilities_.GetShades(row, col, class_labels);
                char shade = data_value.GetFeatureMatrix().GetValue(row, col);

                if (shade == ' ') {
                    shade_counts[kWhiteShadeValue]++;
                } else if (shade == '+' || shade == '#') {
                    shade_counts[kBlackShadeValue]++;
                }
            }
        }

        /*
        //divide each shade count by 2k + number of training images of labelled 'c' to get the conditional probability
        for (size_t row = 0; row < kRowSize; row++) {
            for (size_t col = 0; col < kColSize; col++) {
                for (size_t class_label = 0; class_label < class_counts.size(); class_label++) {
                    for (int shade = 0; shade < kNumShades; shade++) {
                        double numerator = conditional_probabilities_.GetValue(row, col, class_label, shade);
                        double denominator = kLaplaceSmoothingValue * kNumShades + class_counts[class_label];
                        conditional_probabilities_.SetValue(row, col, class_label, shade) =
                                (double) numerator / denominator;
                    }
                }
            }
        }


        //calculate the prior probabilities using formula from instructions
        for (size_t index = 0; index < class_counts.size(); index++) {
            double prior_probability = (kLaplaceSmoothingValue + class_counts[index]) /
                                       (kPossibleClassNum * kLaplaceSmoothingValue + num_training_images_);
            prior_probabilities_.push_back(prior_probability);
        }
        */
    }
}

FourDimensional_Vector Naive_Bayes_Model::GetConditionalProbabilities() {
    return conditional_probabilities_;
}

vector<double> Naive_Bayes_Model::GetPriorProbabilities() {
    return prior_probabilities_;
}
}