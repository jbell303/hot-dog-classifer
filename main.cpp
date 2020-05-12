/**  Hot Dog Classifer
/   by James Bell
/   Modified from original project by Microsoft ELL team
**/
#include <chrono>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <stdio.h>
#include <stdexcept>

// Include the model interface file for the compiled ELL model
// Note: the "<modelname>_MAIN" preprocessor symbol must be defined in exactly one source file
//       that includes the model interface file. This is typically the file that defines "main()"
#define model_MAIN
#include "model.h"

// Include helper functions
#include "tutorialHelpers.h"

// include classifier
#include "classifier.h"

int main(int argc, char** argv)
{
    // parse command line arguments
    cv::CommandLineParser parser(argc, argv,
        "{help h||}"
        "{@image i||Path to image file.}"
        "{@categories c||Path to categories txt file.}");
        //"{camera|0|Camera device number.}");
    
    parser.about("\nThis program uses the ELL pre-trained model to classify images.\n"
        "You can use an existing image file or the camera.\n\n");
    parser.printMessage();
    std::string image_filepath = parser.get<std::string>("@image");
    std::string image = cv::samples::findFile(image_filepath);
    std::string categories_filepath = parser.get<std::string>("@categories");
    std::string categories = cv::samples::findFile(categories_filepath);
    
    // initialize the model
    ModelWrapper wrapper;

    // initialize classifier
    Classifier classifier(image, categories);

    // Open the video camera. To use a different camera, change the camera index.
    //cv::VideoCapture camera(0);

    while ((cv::waitKey(1) & 0xFF) != 27)
    {
        // classifiy the image
        std::vector<float> predictions = classifier.Predict();

        // Get the value of the top 5 predictions
        auto top1 = tutorialHelpers::GetTopN(predictions, 1);

        // Generate header text that represents the top5 predictions
        std::stringstream headerText;
        cv::Scalar color;
        for (auto element : top1)
        {
            if (element.first == 934)
            {
                headerText << "(" << std::floor(element.second * 100.0) << "%) " << classifier.Categories()[element.first] << "  ";
                color = cv::Scalar(50, 200, 50); // green
            }
            else 
            {
                headerText << "not hot dog " << "(" << std::floor(element.second * 100) << "%) "<< classifier.Categories()[element.first] << "  ";
                color = cv::Scalar(50, 50, 200); // red
            }
            
        }
        tutorialHelpers::DrawHeader(classifier.Image(), headerText.str(), color);

        // Generate footer text that represents the mean evaluation time
        /*std::stringstream footerText;
        meanTimeToPredict = std::floor(tutorialHelpers::GetMeanDuration(predictionTimes, std::chrono::duration<double>(end - start).count()) * 1000);
        footerText << meanTimeToPredict << "ms/frame";
        tutorialHelpers::DrawFooter(image, footerText.str());*/

        // Display the image
        cv::imshow("ELL model", classifier.Image());
    }

    //std::cout << "Mean prediction time: " << meanTimeToPredict << "ms/frame" << std::endl;

    return 0;
}