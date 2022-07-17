#include "webcam.h"

Webcam::Webcam(int webcamNumber, std::string nameWindows)
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
        capture.read(this->img);
        cv::imshow(this->nameWindows, this->img);
        cv::waitKey(1);
    }
}

void Webcam::run_color_dectection_with_track_bar()
{
    /***
     * Amarelo: 
     * Hue Min = 18
     * Hue Max = 48
     * Sat Min = 160
     * Sat Man = 255
     * Val Min = 109
     * Val Max = 255
     * 
     */ 


    int hmin = 0, smin = 0, vmin = 0;
    int hmax = 255, smax = 255, vmax = 255;

    std::string windowName = "Trackbars";
    cv::Mat mask, imgHVS;
    // Converter a imagem para HVS

    cv::namedWindow(windowName, (200, 400));
    cv::createTrackbar("Hue Min", windowName, &hmin, 179);
    cv::createTrackbar("Hue Max", windowName, &hmax, 179);
    cv::createTrackbar("Sat Min", windowName, &smin, 255);
    cv::createTrackbar("Sat Max", windowName, &smax, 255);
    cv::createTrackbar("Val Min", windowName, &vmin, 255);
    cv::createTrackbar("Val Max", windowName, &vmax, 255);

    while (true)
    {
        capture.read(this->img);
        cv::cvtColor(img, imgHVS, cv::COLOR_BGR2HSV);
        
        cv::Scalar lower(hmin, smin, vmin);
        cv::Scalar upper(hmax, smax, vmax);

        cv::inRange(imgHVS, lower, upper, mask);


        cv::imshow(this->nameWindows, mask);
        cv::waitKey(1);
    }
}