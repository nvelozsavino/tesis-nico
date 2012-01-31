#include "controller.h"

Controller::Controller() {

}


bool Controller::openImage(QString fileName){
    VideoCapture capture;
    capture.open(fileName.toAscii().data());
    if (capture.isOpened()){
        capture>>image;
        //imshow("imagen",image);
        isOpen=true;
        return true;
    } else {
        isOpen=false;
        return false;
    }
}

void Controller::displayImage(QImage *img){

    if (isOpen){
        Mat temp;
        //imshow("image",image);
        //temp.create(image.size(),image.type());
        //image.copyTo(temp);
        //imshow("temp1",temp);
        cvtColor(image,temp,CV_BGR2RGB);
        //imshow("temp2",image);
        *img=QImage((const unsigned char*)(temp.data), temp.cols,temp.rows,QImage::Format_RGB888);
    }

}
