cmake_minimum_required(VERSION 2.8)

project(tutorial)

set(OPENCV_DIR "C:/opencv/build/")

find_package(OpenCV REQUIRED)

add_subdirectory(model)

add_executable(tutorial tutorial.cpp)

target_link_libraries(tutorial ${OpenCV_LIBS} model)