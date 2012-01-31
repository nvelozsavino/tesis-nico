#include <FeatureTracker.h>



FeatureTracker::~FeatureTracker()
{
    //dtor
}


void FeatureTracker::process(cv:: Mat &frame, cv:: Mat &output) {
    // convert to gray-level image
    cv::cvtColor(frame, gray, CV_BGR2GRAY);
    frame.copyTo(output);
    // 1. if new feature points must be added
    if(addNewPoints()) {
        // detect feature points
        detectFeaturePoints();
        // add the detected features to
        // the currently tracked features
        points[0].insert(points[0].end(),
        features.begin(),features.end());
        initial.insert(initial.end(),
        features.begin(),features.end());
    }
    // for first image of the sequence
    if(gray_prev.empty()){
        gray.copyTo(gray_prev);
    }
    // 2. track features
    cv::calcOpticalFlowPyrLK(gray_prev, gray, points[0], points[1], status, err);

    // 2. loop over the tracked points to reject some
    int k=0;
    for( int i= 0; i < points[1].size(); i++ ) {
        // do we keep this point?
        if (acceptTrackedPoint(i)) {
            // keep this point in vector
            initial[k]= initial[i];
            points[1][k++] = points[1][i];
        }
    }
    // eliminate unsuccesful points
    points[1].resize(k);
    initial.resize(k);
    // 3. handle the accepted tracked points
    handleTrackedPoints(frame, output);
    // 4. current points and image become previous ones
    std::swap(points[1], points[0]);
    cv::swap(gray_prev, gray);
}

// feature point detection
void FeatureTracker::detectFeaturePoints() {
    // detect the features

    cv::goodFeaturesToTrack(gray,       // the image
                            features,  // the output detected features
                            max_count, // the maximum number of features
                            qlevel,    // quality level
                            minDist);  // min distance between two features

}

// determine if new points should be added
bool FeatureTracker::addNewPoints() {
    // if too few points
    return points[0].size()<=10;
}

// determine which tracked point should be accepted
bool FeatureTracker::acceptTrackedPoint(int i) {
    return status[i] && (abs(points[0][i].x-points[1][i].x)+(abs(points[0][i].y-points[1][i].y))>2);
}


// handle the currently tracked points
void FeatureTracker::handleTrackedPoints(cv:: Mat &frame, cv:: Mat &output) {
    // for all tracked points
    for(int i= 0; i < points[1].size(); i++ ) {
        // draw line and circle
        cv::line(output,
        initial[i], // initial position
        points[1][i],// new position
        cv::Scalar(255,255,255));
        cv::circle(output, points[1][i], 3,
        cv::Scalar(255,255,255),-1);
    }
}
