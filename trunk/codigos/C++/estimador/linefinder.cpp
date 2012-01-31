#include "linefinder.h"


// Set the resolution of the accumulator
void LineFinder::setAccResolution(double dRho, double dTheta) {
    deltaRho= dRho;
    deltaTheta= dTheta;
}

// Set the minimum number of votes
    void LineFinder::setMinVote(int minv) {
    minVote= minv;
}

// Set line length and gap
void LineFinder::setLineLengthAndGap(double length, double gap) {
    minLength= length;
    maxGap= gap;
}

// Apply probabilistic Hough Transform
vector<Vec4i> LineFinder::findLines(Mat& binary) {
    lines.clear();
    HoughLinesP(binary,lines, deltaRho, deltaTheta, minVote, minLength, maxGap);
    return lines;
}


// Draw the detected lines on an image
void LineFinder::drawDetectedLines(Mat &image, Scalar color) {
    // Draw the lines
    vector<Vec4i>::const_iterator it2= lines.begin();
    while (it2!=lines.end()) {
        Point pt1((*it2)[0],(*it2)[1]);
        Point pt2((*it2)[2],(*it2)[3]);
        line( image, pt1, pt2, color);
        ++it2;
    }
}
