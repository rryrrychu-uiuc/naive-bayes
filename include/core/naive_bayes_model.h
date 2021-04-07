#include <vector>
#include "matrix.h"
#include "training_data.h"
#include "fourdimensional_vector.h"

using std::vector;

#ifndef NAIVE_BAYES_NAIVE_BAYES_MODEL_H
#define NAIVE_BAYES_NAIVE_BAYES_MODEL_H
namespace naivebayes {
    class Naive_Bayes_Model {
    public:

        /**
         * Create an empty model with no values
         */
        Naive_Bayes_Model(size_t row_size, size_t col_size);

        /**
         * Create a model from a vector of training vectors
         */
        Naive_Bayes_Model(vector<Training_Data> dataset);

        FourDimensional_Vector GetConditionalProbabilities();

        vector<double> GetPriorProbabilities();

        friend std::istream &operator>>(std::istream &is, Naive_Bayes_Model &bayes_model);

        friend std::ostream &operator<<(std::ostream &is, Naive_Bayes_Model &bayes_model);

    private:
        const int kLaplaceSmoothingValue;
        const int kPossibleClassNum;
        const int kBlackShadeValue;
        const int kWhiteShadeValue;
        const size_t kRowSize;
        const size_t kColSize;
        int num_training_images_;

        vector<double> prior_probabilities_;

        //4d vector formatted like [row][col][class_label][shade]
        FourDimensional_Vector conditional_probabilities_;

        //counts the number of various shades for every training image
        vector<int> CountShadesAndClasses(vector<Training_Data> dataset);

        //divide each shade count by 2k + number of training images of labelled 'c' to get the conditional probability
        void CalculateConditionalProbabilities(vector<int> class_counts);

        //calculate the prior probabilities using formula from instructions and the counts of each class
        void CalculatePriorProbabilities(vector<int> class_counts);
    };
}
#endif //NAIVE_BAYES_NAIVE_BAYES_MODEL_H
