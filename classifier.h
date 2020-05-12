// Hot Dog Classifier Class
#ifndef HOT_DOG
#define HOT_DOG

#include <opencv2/opencv.hpp>

// Include the model interface file for the compiled ELL model
// Note: the "<modelname>_MAIN" preprocessor symbol must be defined in exactly one source file
//       that includes the model interface file. This is typically the file that defines "main()"
#define model_MAIN
#include "model.h"

class Classifier {
public:
    // constructor with image file
    Classifier(const std::string& imageFile, const std::string& categoryFile);

    // read an image from the camera
    cv::Mat GetImageFromCamera(cv::VideoCapture& camera);

    // read an image from a file
    std::shared_ptr<cv::Mat> GetImageFromFile(const std::string& filename);

    // read a file of strings
    std::vector<std::string> ReadLinesFromFile(const std::string& filename);

    std::vector<float> Predict();

    cv::Mat Image();

    std::vector<std::string> Categories();

private:
    std::shared_ptr<cv::Mat> _image;
    std::vector<std::string> _categories;
    ModelWrapper _model;
};
#endif // !HOT_DOG
