#ifndef FRAMEPROCESSOR_H
#define FRAMEPROCESSOR_H


#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class FrameProcessor
{
    public:
        FrameProcessor();
        virtual ~FrameProcessor();
        virtual void process(cv:: Mat &input, cv:: Mat &output)= 0;
    protected:
    private:
};

#endif // FRAMEPROCESSOR_H
