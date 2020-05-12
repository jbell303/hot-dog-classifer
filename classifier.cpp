// hotDogClassifier.cpp
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>

#include "classifier.h"

// include helper functions
#include "tutorialHelpers.h"

Classifier::Classifier(const std::string& imageFile, const std::string& categoryFile)
{
	_image = GetImageFromFile(imageFile);
	_categories = ReadLinesFromFile(categoryFile);
}

cv::Mat Classifier::GetImageFromCamera(cv::VideoCapture& camera)
{
	cv::Mat frame;
	camera >> frame;
	return frame;
}

std::shared_ptr<cv::Mat> Classifier::GetImageFromFile(const std::string& filename)
{
	cv::Mat img;
	try 
	{
		img = cv::imread(filename, cv::IMREAD_COLOR);
	}
	catch (...)
	{
		std::cout << "could not read the image: " << filename << std::endl;
		exit(0);
	}
	return std::make_shared<cv::Mat>(img);
}

std::vector<std::string> Classifier::ReadLinesFromFile(const std::string& filename)
{
	std::vector<std::string> lines;
	std::string line;

	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cout << "could not open file: " << filename << std::endl;
	}
	else
	{
		while (std::getline(file, line))
		{
			if (line.length() > 0)
				lines.emplace_back(line);
		}
		return lines;
	}
}

std::vector<float> Classifier::Predict()
{
	// get the model's input shape
	TensorShape inputShape = _model.GetInputShape();

	// get the model's preprocessing data
	tutorialHelpers::ImagePreprocessingMetadata metadata = tutorialHelpers::GetImagePreprocessingMetadata(_model);

	// create a vector to hold the model's output predictions
	std::vector<float> predictions(_model.GetOutputSize());

	// preprocess the image
	auto input = tutorialHelpers::PrepareImageForModel(*_image, inputShape.columns, inputShape.rows, &metadata);

	// generate predictions
	predictions = _model.Predict(input);

	return predictions;
}

cv::Mat Classifier::Image()
{
	return *_image;
}

std::vector<std::string> Classifier::Categories()
{
	return _categories;
}


