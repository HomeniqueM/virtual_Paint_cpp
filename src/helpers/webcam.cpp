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
    int hmin = 0, smin = 0, vmin = 0;
    int hmax = 179, smax = 255, vmax = 255;

    std::string windowName = "Trackbars";
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
        findColor(hmin, smin, vmin, hmax, smax, vmax);

        cv::imshow(this->nameWindows, imgMask);
        cv::waitKey(1);
    }
}

void Webcam::findColor(int hmin, int smin, int vmin, int hmax, int smax, int vmax)
{
    findColor(std::vector<std::vector<int>>{{hmin, smin, vmin, hmax, smax, vmax}});
}

void Webcam::findColor(std::vector<std::vector<int>> myColors)
{
    cv::cvtColor(this->img, this->imgHVS, cv::COLOR_BGR2HSV);
    for (int i = 0; i < myColors.size(); i++)
    {
        cv::Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
        cv::Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);

        std::cout << myColors[i][0] << "," << myColors[i][1] << "," << myColors[i][2] << ","
                  << myColors[i][3] << "," << myColors[i][4] << "," << myColors[i][5] << "\n";
        cv::inRange(this->imgHVS, lower, upper, this->imgMask);
    }
}

void Webcam::run_and_drawing()
{
    std::vector<std::vector<int>> myColors{{18, 160, 109, 48, 255, 255}, // Amarelo
                                           {0, 189, 112, 12, 255, 255}}; // Laranja

    std::vector<cv::Scalar> myColorValues{{68, 277, 224}, // Amarelo
                                          {30, 94, 241}}; // Laranja

    while (true)
    {
        capture.read(this->img);

        cv::cvtColor(this->img, this->imgHVS, cv::COLOR_BGR2HSV);
        for (int i = 0; i < myColors.size(); i++)
        {
            cv::Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
            cv::Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
            cv::inRange(this->imgHVS, lower, upper, this->imgMask);

            getContours(imgMask);
            cv::imshow(this->nameWindows, this->img);
        }

        cv::waitKey(1);
    }
}

cv::Point Webcam::getContours(cv::Mat imgDill)
{
    int contoursSize = 0;
    float perimeter;
    cv::Point myPoint(0, 0);
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    std::string objectType;
    cv::findContours(imgDill, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    contoursSize = contours.size();

    std::vector<std::vector<cv::Point>> conPoly(contoursSize);
    std::vector<cv::Rect> boundRect(contoursSize);

    for (int i = 0; i < contoursSize; i++)
    {

        int area = cv::contourArea(contours[i]);

        if (area > 50)
        {
            perimeter = cv::arcLength(contours[i], true);
            cv::approxPolyDP(contours[i], conPoly[i], 0.02 * perimeter, true);
           
            boundRect[i] = cv::boundingRect(conPoly[i]);
            myPoint.x = boundRect[i].x + boundRect[i].width / 2;
            myPoint.y = boundRect[i].y;
          

            cv::drawContours(this->img, conPoly, i, cv::Scalar(255, 0, 255), 2);
            cv::rectangle(this->img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(200, 255, 0), 5);
        }
    }

    return myPoint;
}