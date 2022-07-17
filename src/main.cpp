#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "helpers/webcam.hpp"


int main(int argc, char const *argv[])
{
    Webcam *cam = new Webcam();

    cam->run();
    return 0;
}
