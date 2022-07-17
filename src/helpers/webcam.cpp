#include "webcam.hpp"

Webcam::Webcam(int webcamNumber,std::string nameWindows)
{
    this->webcamNumber = webcamNumber;
    this->capture = cv::VideoCapture(webcamNumber);
    this->nameWindows = nameWindows;
}

Webcam::~Webcam()
{
    capture.~VideoCapture();
    img.~Mat();
}
void Webcam::run()
{
    while (true)
    {
        capture.read(img);
        cv::imshow(nameWindows, img);
        cv::waitKey(1);
    }
}