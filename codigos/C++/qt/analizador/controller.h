#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QImage>
#include <QString>

#include <linefinder.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


class Controller {
private:
    LineFinder *linefinder;
    Mat image;
    Mat result;
    bool isOpen;
public:

    void displayImage(QImage *img);
    bool openImage(QString fileName);
    Controller();
};

#endif // CONTROLLER_H
