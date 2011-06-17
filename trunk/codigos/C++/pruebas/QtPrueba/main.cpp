#include <QtGui/QApplication>
#include "mainwindow.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    Mat img;

    img = imread("c:/imagen.jpg",1);
    //imshow("imagen",img);
    QApplication a(argc, argv);
    MainWindow w;
    w.setImg(img);
    w.show();

    return a.exec();
}
