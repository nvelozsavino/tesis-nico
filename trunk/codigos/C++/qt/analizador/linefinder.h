#ifndef LINEFINDER_H
#define LINEFINDER_H

#include <opencv2/opencv.hpp>
#include <stdlib.h>
#define USE_MATH_DEFINES
#include <math.h>

using namespace cv;
using namespace std;

class LineFinder {

private:
    // original image
    Mat img;

    // vector containing the end points
    // of the detected lines
    vector<Vec4i> lines;

    // accumulator resolution parameters
    double deltaRho;
    double deltaTheta;

    // minimum number of votes that a line
    // must receive before being considered
    int minVote;

    // min length for a line
    double minLength;

    // max allowed gap along the line
    double maxGap;

public:
    // Default accumulator resolution is 1 pixel by 1 degree
    // no gap, no mimimum length
    LineFinder() : deltaRho(1), deltaTheta(M_PI/180), minVote(10), minLength(0.), maxGap(0.) {}


    // Set the resolution of the accumulator
    void setAccResolution(double dRho, double dTheta);

    // Set the minimum number of votes
    void setMinVote(int minv);

    // Set line length and gap
    void setLineLengthAndGap(double length, double gap);

    // Apply probabilistic Hough Transform
    vector<Vec4i> findLines(Mat& binary);

    // Draw the detected lines on an image
    void drawDetectedLines(Mat &image, Scalar color);

};



#endif // LINEFINDER_H
