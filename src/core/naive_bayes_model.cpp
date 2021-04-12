#include <string>
#include <sstream>
#include "core/naive_bayes_model.h"

const int kNumShades = 2;
using std::to_string;

namespace naivebayes {

    NaiveBayesModel::NaiveBayesModel(size_t row_size, size_t col_size) :
            kRowSize(row_size),
            kColSize(col_size),
            kShadedValue(0),
            kUnshadedValue(1),
            kLaplaceSmoothingValue(1),
            kPossibleClassNum(10),
            conditional_probabilities_(kRowSize, kColSize, kPossibleClassNum, 2, kLaplaceSmoothingValue) {

    }

    NaiveBayesModel::NaiveBayesModel(vector<TrainingData> dataset) :
            num_training_images_(dataset.size()),
            kRowSize(dataset[0].GetRowSize()),
            kColSize(dataset[0].GetColSize()),
            kShadedValue(0),
            kUnshadedValue(1),
            kLaplaceSmoothingValue(1),
            kPossibleClassNum(10),
            conditional_probabilities_(kRowSize, kColSize, kPossibleClassNum, 2, kLaplaceSmoothingValue) {

        vector<int> class_counts = CountShadesAndClasses(dataset);
        CalculateConditionalProbabilities(class_counts);
        CalculatePriorProbabilities(class_counts);
    }

    vector<int> NaiveBayesModel::CountShadesAndClasses(vector<TrainingData> dataset) {
        vector<int> class_counts(kPossibleClassNum);

        //determine the counts for the shades from the training data
        for (TrainingData data_value : dataset) {

            //counts number of each class in training data
            int class_labels = data_value.GetClassLabel();
            class_counts[class_labels]++;

            //count the shades for each of the classes on each index in the matrix
            for (size_t row = 0; row < data_value.GetRowSize(); row++) {
                for (size_t col = 0; col < data_value.GetColSize(); col++) {
                    vector<double> shade_counts = conditional_probabilities_.GetShades(row, col, class_labels);
                    char shade = data_value.GetValue(row, col);

                    if (shade == ' ') {
                        conditional_probabilities_.SetValue(row, col, class_labels, kUnshadedValue,
                                                            shade_counts[kUnshadedValue] + 1);
                    } else if (shade == '+' || shade == '#') {
                        conditional_probabilities_.SetValue(row, col, class_labels, kShadedValue,
                                                            shade_counts[kShadedValue] + 1);
                    }
                }
            }
        }
        return class_counts;
    }

    void NaiveBayesModel::CalculateConditionalProbabilities(vector<int> class_counts) {
        for (size_t row = 0; row < kRowSize; row++) {
            for (size_t col = 0; col < kColSize; col++) {
                for (size_t class_label = 0; class_label < class_counts.size(); class_label++) {
                    for (int shade = 0; shade < kNumShades; shade++) {
                        double numerator = conditional_probabilities_.GetValue(row, col, class_label, shade);
                        double denominator = kLaplaceSmoothingValue * kNumShades + class_counts[class_label];
                        conditional_probabilities_.SetValue(row, col, class_label, shade,
                                                            (double) numerator / denominator);
                    }
                }
            }
        }
    }

    void NaiveBayesModel::CalculatePriorProbabilities(vector<int> class_counts) {

        for (size_t index = 0; index < class_counts.size(); index++) {
            double prior_probability = (double) (kLaplaceSmoothingValue + class_counts[index]) /
                                       (kPossibleClassNum * kLaplaceSmoothingValue + num_training_images_);
            prior_probabilities_.push_back(prior_probability);
        }
    }
    
    FourDimensional_Vector NaiveBayesModel::GetConditionalProbabilities() {
        return conditional_probabilities_;
    }

    vector<double> NaiveBayesModel::GetPriorProbabilities() {
        return prior_probabilities_;
    }

    double NaiveBayesModel::GetConditionalProbability(size_t row, size_t col, int class_label, int shade) {
        return conditional_probabilities_.GetValue(row, col, class_label, shade);
    }
    
    double NaiveBayesModel::GetPriorProbability(int class_label) {
        
        if(class_label < 0 || class_label > 9) {
            throw std::invalid_argument("Class must be between 0 and 9 (inclusive)");
        }
        
        return prior_probabilities_[class_label];
    }
    
    std::istream &operator>>(std::istream &is, NaiveBayesModel &bayes_model) {

        vector<size_t> sizes;

        //gets the sizes from first line of file
        std::string line;
        std::string::size_type size_value;
        std::getline(is, line);
        std::stringstream line_stream(line);
        std::string value_str;
        while (line_stream >> value_str) {
            sizes.push_back(std::stoi(value_str, &size_value));
        }

        //gets all of the data based on coordinates and shades
        while (!is.eof()) {

            //gets the row and column of the first two dimensions of the 4d vector
            vector<int> position;
            std::getline(is, line);
            std::stringstream locations(line);
            std::string coordinate;
            while (locations >> coordinate) {
                position.push_back(std::stoi(coordinate));
            }

            //next lines are the shades associated with each class
            for (size_t class_label = 0; class_label < sizes[2]; class_label++) {

                //extracts the shades from a line
                std::getline(is, line);
                std::stringstream shade_probabilities(line);
                std::string individual_shade;

                //place them in the correct index of the 4th level vector
                size_t shade_index = 0;
                while (shade_probabilities >> individual_shade && shade_index < sizes[3]) {
                    double shadeValue = std::stod(individual_shade);
                    bayes_model.GetConditionalProbabilities().SetValue(position[0], position[0], class_label,
                                                                       shade_index, shadeValue);
                }
            }
        }

        return is;
    }

    std::ostream &operator<<(std::ostream &os, NaiveBayesModel &bayes_model) {
        FourDimensional_Vector values = bayes_model.GetConditionalProbabilities();
        //print out four key sizes of 4d vector
        os << to_string(values.GetRowSize()) << " " << to_string(values.GetColSize()) << " "
           << to_string(values.GetClassSize()) << " " << to_string(values.GetShadeSize()) << std::endl;

        //print out the row/col then the shades
        for (size_t row = 0; row < values.GetRowSize(); row++) {
            for (size_t col = 0; col < values.GetColSize(); col++) {
                os << to_string(row) << " " << to_string(col) << std::endl;
                for (size_t class_label = 0; class_label < values.GetClassSize(); class_label++) {
                    for (size_t shade = 0; shade < values.GetShadeSize(); shade++) {
                        os << to_string(values.GetValue(row, col, class_label, shade));
                        if (shade != values.GetShadeSize() - 1) {
                            os << " ";
                        }
                    }
                    os << std::endl;
                }
                os << std::endl;
            }
        }

        return os;
    }
} //namespace naivebayes