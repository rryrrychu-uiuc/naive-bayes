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
    
    vector<int> class_counts = CountShadesAndClasses(dataset);
    CalculateConditionalProbabilities(class_counts);
    CalculatePriorProbabilities(class_counts);
}

vector<int> Naive_Bayes_Model::CountShadesAndClasses(vector<Training_Data> dataset) {
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
                    conditional_probabilities_.SetValue(row, col, class_labels, kWhiteShadeValue, shade_counts[kWhiteShadeValue]+1);
                } else if (shade == '+' || shade == '#') {
                    conditional_probabilities_.SetValue(row, col, class_labels, kBlackShadeValue, shade_counts[kBlackShadeValue]+1);
                }
            }
        }
    }
    return class_counts;
}

void Naive_Bayes_Model::CalculateConditionalProbabilities(vector<int> class_counts) {
    for (size_t row = 0; row < kRowSize; row++) {
        for (size_t col = 0; col < kColSize; col++) {
            for (size_t class_label = 0; class_label < class_counts.size(); class_label++) {
                for (int shade = 0; shade < kNumShades; shade++) {
                    double numerator = conditional_probabilities_.GetValue(row, col, class_label, shade);
                    double denominator = kLaplaceSmoothingValue * kNumShades + class_counts[class_label];
                    conditional_probabilities_.SetValue(row, col, class_label, shade, (double) numerator / denominator);
                }
            }
        }
    }
}

void Naive_Bayes_Model::CalculatePriorProbabilities(vector<int> class_counts) {
    
    for (size_t index = 0; index < class_counts.size(); index++) {
        double prior_probability = (double)(kLaplaceSmoothingValue + class_counts[index]) /
                                   (kPossibleClassNum * kLaplaceSmoothingValue + num_training_images_);
        prior_probabilities_.push_back(prior_probability);
    }
}

FourDimensional_Vector Naive_Bayes_Model::GetConditionalProbabilities() {
    return conditional_probabilities_;
}

vector<double> Naive_Bayes_Model::GetPriorProbabilities() {
    return prior_probabilities_;
}

std::istream &operator>>(std::istream& is, Naive_Bayes_Model& bayes_model) {
    
}

std::ostream &operator<<(std::ostream& os, Naive_Bayes_Model& bayes_model) {
    FourDimensional_Vector values = bayes_model.GetConditionalProbabilities()
    for(size_t i = 0; i < 3; i++) {
        for(size_t j = 0; j < 3; j++) {
            os << i << "," << j;
            for(size_t k = 0; k < 10; k++) {
                std::cout << "Class " << k << ": [ ";
                for(size_t l = 0; l < 2; l++) {
                    REQUIRE(small_picture.GetValue(i,j,k,l) == 1);
                    std::cout << small_picture.GetValue(i,j,k,l) << " ";
                }
                std::cout << "]" << std::endl;
            }
            std::cout << std::endl;
        }
    }
}
} //namespace naivebayes