#ifndef CVWEBCAM_HPP
#define CVWEBCAM_HPP
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class Webcam
{
private:
    cv::Mat img, imgMask, imgHVS;
    
    cv::VideoCapture capture;
    int webcamNumber;
    std::string nameWindows;
    std::vector<std::vector<int>> vPoints;

    void findColor(int hmin, int smin, int vmin, int hmax, int smax, int vmax);
    void createHSVTrackBar(int hmin, int smin, int vmin, int hmax, int smax, int vmax);
    cv::Point getContours(cv::Mat imgDill);
    void findColor(std::vector<std::vector<int>> myColors);
    void drawOnCanvas(std::vector<cv::Scalar> myColorValues );

public:
    Webcam(int webcamNumber = 0, std::string nameWindows = "WebCam");
    ~Webcam();
    void run();
    void run_color_dectection_with_track_bar();
    void run_and_drawing();
};

#endif