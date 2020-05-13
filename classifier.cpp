// hotDogClassifier.cpp
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>

#include "classifier.h"

// include helper functions
#include "tutorialHelpers.h"

Classifier::Classifier(const std::string& imageFile, const std::string& categoryFile)
{
	GetImageFromFile(imageFile);
	ReadLinesFromFile(categoryFile);
}

void Classifier::GetImageFromCamera(cv::VideoCapture& camera)
{
	cv::Mat frame;
	camera >> frame;
	_image = frame;
}

void Classifier::GetImageFromFile(const std::string& filename)
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
	_image = img;
}

void Classifier::ReadLinesFromFile(const std::string& filename)
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
		_categories = lines;
	}
}

void Classifier::GetMetadata()
{
	// get the model's input shape
	_inputShape = _model.GetInputShape();
	
	// get the model's preprocessing data
	_metadata = tutorialHelpers::GetImagePreprocessingMetadata(_model);
	
	// create a vector to hold the model's output predictions
	_predictions = std::vector<float>(_model.GetOutputSize());
}

std::vector<float> Classifier::Predict()
{
	// preprocess the image
	auto input = tutorialHelpers::PrepareImageForModel(_image, _inputShape.columns, _inputShape.rows, &_metadata);

	// generate predictions
	_predictions = _model.Predict(input);

	return _predictions;
}

cv::Mat Classifier::Image()
{
	return _image;
}

std::vector<std::string> Classifier::Categories()
{
	return _categories;
}

