#pragma once
#include <vector>
#include "matrix.h"
#include "training_data.h"
#include "fourdimensional_vector.h"

using std::vector;

#ifndef NAIVE_BAYES_NAIVE_BAYES_MODEL_H
#define NAIVE_BAYES_NAIVE_BAYES_MODEL_H
namespace naivebayes {
    class NaiveBayesModel {
    public:

        /**
         * Create an empty model with no values
         */
        NaiveBayesModel(size_t row_size, size_t col_size);

        /**
         * Create a model from a vector of training vectors
         */
        NaiveBayesModel(vector<TrainingData> dataset);

        FourDimensional_Vector GetConditionalProbabilities();

        vector<float> GetPriorProbabilities();

        float GetConditionalProbability(size_t row, size_t col, int class_label, int shade);

        float GetPriorProbability(int class_label);

        void SetProbabilityValue(size_t row, size_t col, size_t class_label, size_t shade, float val);
        
        void SetPriorValue(size_t class_label, float val);

        void AddPriorValue(float val);
        
        void Print();
        
        friend std::istream &operator>>(std::istream &is, NaiveBayesModel &bayes_model);

        friend std::ostream &operator<<(std::ostream &is, NaiveBayesModel &bayes_model);

    private:
        const float kLaplaceSmoothingValue;
        const int kPossibleClassNum;
        const int kShadedValue;
        const int kUnshadedValue;
        const size_t kRowSize;
        const size_t kColSize;
        int num_training_images_;

        vector<float> prior_probabilities_;

        //4d vector formatted like [row][col][class_label][shade]
        FourDimensional_Vector conditional_probabilities_;

        //counts the number of various shades for every training image
        vector<int> CountShadesAndClasses(vector<TrainingData> dataset);

        //divide each shade count by 2k + number of training images of labelled 'c' to get the conditional probability
        void CalculateConditionalProbabilities(vector<int> class_counts);

        //calculate the prior probabilities using formula from instructions and the counts of each class
        void CalculatePriorProbabilities(vector<int> class_counts);
        
    };
}
#endif //NAIVE_BAYES_NAIVE_BAYES_MODEL_H
