#include <algorithm>
#include "core/classifier.h"

Classifier::Classifier(NaiveBayesModel target_model, size_t row, size_t col): trained_model_(target_model){
    row_size = row;
    col_size = col;
}

int Classifier::GetPredictedValue(Matrix image) {
    vector<float> likelihood_scores = CalculateLikelihoodScores(image);
    
    int max_index = 0;
    float max_value = -1;
    
    for(size_t index = 0; index < likelihood_scores.size(); index++) {
        if(likelihood_scores[index] > max_value) {
            max_index = index;
            max_value = likelihood_scores[index];
        }
    }
    
    
    return max_index;
}

vector<float> Classifier::CalculateLikelihoodScores(Matrix image) {
    
    vector<float> likelihood_scores;
    
    for(int class_label = 0; class_label <= 9; class_label++){
        float likelihood_score = log((float)trained_model_.GetPriorProbability(class_label));
        
        for(size_t row = 0; row < image.GetRowSize(); row++) {
            for(size_t col = 0; col < image.GetColSize(); col++) {
                int pixel_value = 0;
                if(image.GetValue(row, col) == kUnshadedPixel) {
                    pixel_value = kUnshadedValue;
                } else {
                    pixel_value = kShadedValue;
                }
                likelihood_score += log((float)trained_model_.GetConditionalProbability(row, col, class_label, pixel_value));
            }
        }
        likelihood_scores.push_back(likelihood_score);
    }
    
    return likelihood_scores;
}

size_t Classifier::GetRowSize() {
    return row_size;
}

size_t Classifier::GetColSize() {
    return col_size;
}
