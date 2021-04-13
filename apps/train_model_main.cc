#include <core/naive_bayes_model.h>
#include <iostream>
#include <fstream>
#include <core/image_processor.h>
#include <core/classifier.h>
#include <core/validator.h>

using naivebayes::NaiveBayesModel;

const int kRowColumnLength = 28;

NaiveBayesModel TrainModel(std::string file_path) {
    ImageProcessor test_process(kRowColumnLength, kRowColumnLength);
    std::ifstream target_file;
    target_file.open(file_path);
    if (target_file.good()) {
        target_file >> test_process;
    } else if (target_file.bad()) {
        throw std::invalid_argument("File doesn't exist");
    }

    return NaiveBayesModel(test_process.GetLabelledImages());
}

NaiveBayesModel LoadModel(std::string file_path) {
    NaiveBayesModel new_model(kRowColumnLength,kRowColumnLength);

    std::ifstream my_file (file_path);
    my_file >> new_model;
    return new_model;
}

void SaveModel(std::string file_path, NaiveBayesModel bayes_model) {
    std::ofstream saved_model;
    saved_model.open (file_path);
    saved_model << bayes_model;
    saved_model.close();
}

float ValidateClassifier(std::string file_path, NaiveBayesModel new_model) {
    Classifier target_classifier(new_model, kRowColumnLength, kRowColumnLength);
    Validator target_validator(target_classifier);

    std::ifstream target_file;
    target_file.open(file_path);
    if (target_file.good()) {
        target_file >> target_validator;
    } else if (target_file.bad()) {
        throw std::invalid_argument("File doesn't exist");
    }
    
    vector<int> determined_classification = target_validator.GetDeterminedClassifications();
    vector<int> labelled_values = target_validator.GetLabelledValues();
    
    std::cout << labelled_values.size() << " " << determined_classification.size() << std::endl;
    for(size_t index = 0; index < labelled_values.size(); index++) {
        std::cout << determined_classification[index] << " " << labelled_values[index] << std::endl;
    }
    
    return target_validator.GetClassifierAccuracy();
}

int main() {

    NaiveBayesModel bayes_model = TrainModel("data/trainingimagesandlabels.txt");
    SaveModel("apps/saved_model.txt", bayes_model);
    
    NaiveBayesModel new_model = LoadModel("apps/saved_model.txt");
    //new_model.Print();

    float accuracy = ValidateClassifier("data/trainingimagesandlabels.txt", new_model);
    
    std::cout << "accuracy:" << accuracy << std::endl;
    return 0;
}
