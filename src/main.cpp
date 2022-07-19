#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "helpers/webcam.h"

void menu()
{
    Webcam *cam = new Webcam();
    int mode;
    do
    {
        std::cout << "Selecione o modo: \n";
        std::cout << "1 - Normal\n";
        std::cout << "2 - Com controle HSV\n";
        std::cout << "0 - Finalizar\n";

        std::cin >> mode;

        switch (mode)
        {
        case 0:
            break;
        case 1:
            cam->run();
            break;
        case 2:
            cam->run_color_dectection_with_track_bar();
            break;

        default:
            std::cout << "\n\nOpção invalida\n\n";
            break;
        }

        std::cout << std::endl;
    } while (mode != 0);
}

int main(int argc, char const *argv[])
{
    Webcam *cam = new Webcam();

    cam->run_and_drawing();

    return 0;
}
