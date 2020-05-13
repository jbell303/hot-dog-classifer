# Hot Dog Classifier
Udacity C++ Nanodegree Capstone Project (Choice 1)


## Getting Started
This project is based on the Microsoft [ELL](https://microsoft.github.io/ELL/) "Getting Started with Image Classification on Raspberry Pi" tutorial found [here](https://microsoft.github.io/ELL/tutorials/Getting-started-with-image-classification-in-cpp/).

## Prerequisites
Install [ELL](https://github.com/microsoft/ELL) on your computer ([Windows](https://github.com/microsoft/ELL/blob/master/INSTALL-Windows.md), [Mac](https://github.com/microsoft/ELL/blob/master/INSTALL-Mac.md), [Linux](https://github.com/microsoft/ELL/blob/master/INSTALL-Ubuntu.md)).

## Installation
* Clone this repo `git clone https://github.com/jbell303/hot-dog-classifier.git`
* `cd hot-dog-classifier`
* Download the [compressed ELL file](https://github.com/Microsoft/ELL-models/raw/master/models/ILSVRC2012/d_I224x224x3CMCMCMCMCMCMC1AS/d_I224x224x3CMCMCMCMCMCMC1AS.ell.zip) into your directory.
* Unzip and rename the file to `model.ell`

### Compile the model

Compiling the model is easiest with the python **wrap** tool.
Use [Anaconda](https://www.anaconda.com/) or MiniConda to start a Python environment
Enter the following to compile the model:
```
python <ELL-root>/tools/wrap/wrap.py --model_file model.ell --language cpp --target pi3 --outdir model
```
where `--target` is `pi3` or `pi0` for Raspberry Pi or `host` if you plan to run the model on the host computer.

### (Optional) Deploy the model to Raspberry Pi
Once the model is compiled, copy the project folder onto your Raspberry Pi
In the deployed project folder, build the program using the following:
```
mkdrir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
cd ..
```
## Run the program
`./hot-dog-classifier -i <path to image> -c <path to categories.txt file>`

## Class Diagram
![class diagram](https://github.com/jbell303/hot-dog-classifier/blob/master/class_diagram.png "Class Diagram")

## Expected behavior
If user enters an image file as a command line argument, the classifier predicts the image as a hot dog or other class in the list of 1000 categories from the model. If the user does not provide an image filepath, the default camera is used and a prediction is run on each frame of video.

## Rubric points
### Loops, functions, I/O
* functions and control structures: `main.cpp` line 47, 66 and others
* file I/O: `main.cpp` line 51, 56
* user input: `main.cpp` line 47 (command line arguments), line 66 (escape key to exit program)

### Object Oriented Programming
* OOP: `classifier.h`, `classifier.cpp`. The `classifier` class encapsulates functions from the ELL tutorial
* Access specifiers: `classifier.h` line 17, 41
* Member initialization lists: `classifier.h` line 22 (not currently used)
* Abstraction: `classifier.cpp` line 73 (additional abstraction performed by helper class)
* Encapsulation: `classifier.h` line 35 (getter function), line 42 (private member variables)
* Function overload: `classifier.h` line 22 (not currently used)

### Memory Management
* Pass-by-referemce: `classifier.h` line 22, 25, 28, 31 (all but 22 present in original tutorial)
* RAII: `classifier.cpp` line 70




