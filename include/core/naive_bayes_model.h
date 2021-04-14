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

        /**
         * Read a model from a file
         */
        friend std::istream &operator>>(std::istream &is, NaiveBayesModel &bayes_model);

        /**
        * Write a model to a file
        */
        friend std::ostream &operator<<(std::ostream &is, NaiveBayesModel &bayes_model);
        
        /**
         * Return all of the probability values
         */
        FourDimensional_Vector GetConditionalProbabilities();

        /**
         * Return all of the prior probabilities
         */
        vector<float> GetPriorProbabilities();

        /**
        * Get a single probability value for a pixel of a certain shade and class
        */
        float GetConditionalProbability(size_t row, size_t col, int class_label, int shade);

        /**
        * Get a single prior probability value
        */
        float GetPriorProbability(int class_label);

        void SetProbabilityValue(size_t row, size_t col, size_t class_label, size_t shade, float val);
        
        void SetPriorValue(size_t class_label, float val);

        void AddPriorValue(float val);
        
        size_t GetRowSize();
        
        size_t GetColSize();
        
        void Print();

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
