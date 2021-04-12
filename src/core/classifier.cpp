#include <algorithm>
#include "core/classifier.h"

Classifier::Classifier(vector<TrainingData> dataset): trained_model_(dataset){}

float Classifier::GetPredictedValue(Matrix image) {
    vector<float> likelihood_scores = CalculateLikelihoodScores(image);
    
    return *std::max_element(likelihood_scores.begin(), likelihood_scores.end());
}

vector<float> Classifier::CalculateLikelihoodScores(Matrix image) {
    
    vector<float> likelihood_scores;
    
    for(int class_label = 0; class_label <= 9; class_label++){
        float likelihood_score = (float)trained_model_.GetPriorProbability(class_label);
        
        for(size_t row = 0; row < image.GetRowSize(); row++) {
            for(size_t col = 0; col < image.GetColSize(); col++) {
                int pixel_value = 0;
                if(image.GetValue(row, col) == kUnshadedPixel) {
                    pixel_value = kUnshadedValue;
                } else {
                    pixel_value = kShadedValue;
                }
                likelihood_score *= (float)trained_model_.GetConditionalProbability(row, col, class_label, pixel_value);
            }
        }
        likelihood_scores.push_back(likelihood_score);
    }
    
    return likelihood_scores;
}

