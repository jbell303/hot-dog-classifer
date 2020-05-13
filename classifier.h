// Hot Dog Classifier Class
#ifndef HOT_DOG
#define HOT_DOG

#include <opencv2/opencv.hpp>

// Include the model interface file for the compiled ELL model
// Note: the "<modelname>_MAIN" preprocessor symbol must be defined in exactly one source file
//       that includes the model interface file. This is typically the file that defines "main()"
#define model_MAIN
#include "model.h"

// include helper definitions
#include "tutorialHelpers.h";

class Classifier {
public:
    // default constructor
    Classifier() {};

    // constructor with image file
    Classifier(const std::string& imageFile, const std::string& categoryFile);

    // read an image from the camera
    void GetImageFromCamera(cv::VideoCapture& camera);

    // read an image from a file
    void GetImageFromFile(const std::string& filename);

    // read a file of strings
    void ReadLinesFromFile(const std::string& filename);

    std::vector<float> Predict();

    cv::Mat Image();

    std::vector<std::string> Categories();

    void GetMetadata();

private:
    cv::Mat _image;
    std::vector<std::string> _categories;
    ModelWrapper _model;
    tutorialHelpers::ImagePreprocessingMetadata _metadata;
    TensorShape _inputShape;
    std::vector<float> _predictions;
};
#endif // !HOT_DOG
