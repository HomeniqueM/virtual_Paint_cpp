#ifndef CVWEBCAM_HPP
#define CVWEBCAM_HPP

#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class Webcam
{
private:
    cv::Mat img;
    cv::VideoCapture capture;
    int webcamNumber;
    std::string nameWindows;

public:
    Webcam(int webcamNumber = 0,std::string nameWindows = "WebCam");
    ~Webcam();
    void run();
};

#endif