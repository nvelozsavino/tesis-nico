#ifndef FEATURETRACKER_H
#define FEATURETRACKER_H


#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <FrameProcessor.h>

using namespace cv;
using namespace std;

class FeatureTracker : public FrameProcessor {
    cv::Mat gray;
    // current gray-level image
    cv::Mat gray_prev;
    // previous gray-level image
    // tracked features from 0->1
    std::vector<cv::Point2f> points[2];
    // initial position of tracked points
    std::vector<cv::Point2f> initial;
    std::vector<cv::Point2f> features; // detected features
    int max_count;
    // maximum number of features to detect
    double qlevel;
    // quality level for feature detection
    double minDist;
    // min distance between two points
    std::vector<uchar> status; // status of tracked features
    std::vector<float> err;
    // error in tracking
    public:
        FeatureTracker() : max_count(500), qlevel(0.01), minDist(10.) {}

        virtual ~FeatureTracker();


        void process(cv:: Mat &frame, cv:: Mat &output);

        // feature point detection
        // feature point detection
        void detectFeaturePoints();

        // determine if new points should be added
        bool addNewPoints();

        // determine which tracked point should be accepted
        bool acceptTrackedPoint(int i);

        void handleTrackedPoints(cv:: Mat &frame, cv:: Mat &output);

    protected:
    private:
};

#endif // FEATURETRACKER_H
