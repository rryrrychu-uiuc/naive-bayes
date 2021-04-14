#include <visualizer/naive_bayes_app.h>

namespace naivebayes {

    namespace visualizer {

        NaiveBayesApp::NaiveBayesApp()
                : sketchpad_(glm::vec2(kMargin, kMargin), kImageDimension,
                             kWindowSize - 2 * kMargin), target_model_(kImageDimension, kImageDimension) {
            ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);

            std::ifstream target_file;
            target_file.open("apps/saved_model.txt");
            target_file >> target_model_;
        }

        void NaiveBayesApp::draw() {
            ci::Color8u background_color(255, 246, 148);  // light yellow
            ci::gl::clear(background_color);

            sketchpad_.Draw();

            ci::gl::drawStringCentered(
                    "Press Delete to clear the sketchpad. Press Enter to make a prediction.",
                    glm::vec2(kWindowSize / 2, kMargin / 2), ci::Color("black"), ci::Font("Times New Roman", 45));

            ci::gl::drawStringCentered(
                    "Prediction: " + std::to_string(current_prediction_),
                    glm::vec2(kWindowSize / 2, kWindowSize - kMargin / 2), ci::Color("blue"), ci::Font("Times New Roman", 45));
        }

        void NaiveBayesApp::mouseDown(ci::app::MouseEvent event) {
            sketchpad_.HandleBrush(event.getPos());
        }

        void NaiveBayesApp::mouseDrag(ci::app::MouseEvent event) {
            sketchpad_.HandleBrush(event.getPos());
        }

        void NaiveBayesApp::keyDown(ci::app::KeyEvent event) {

            Classifier new_classifier(target_model_);
            switch (event.getCode()) {
                case ci::app::KeyEvent::KEY_RETURN:
                    current_prediction_ = new_classifier.GetPredictedClass(sketchpad_.GetImage());
                    break;

                case ci::app::KeyEvent::KEY_DELETE:
                    sketchpad_.Clear();
                    break;
            }
        }

    }  // namespace visualizer

}  // namespace naivebayes
