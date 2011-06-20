#include <QtGui/QApplication>
#include "mainwindow.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    Mat img;
    VideoCapture cap;
    cap.open(0);
    cap.set(CV_CAP_PROP_FRAME_WIDTH,320);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,240);
    cap.set(CV_CAP_PROP_EXPOSURE,100);
    //cap.set(CV_CAP_PROP_GAIN,10);


    //img = imread("c:/imagen.jpg",1);
    //imshow("imagen",img);
    QApplication a(argc, argv);
    MainWindow w(cap);
    //w.setImg(img);
    w.show();
    return a.exec();
}
