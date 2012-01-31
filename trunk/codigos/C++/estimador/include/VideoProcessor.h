#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <iomanip>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <FrameProcessor.h>

using namespace cv;
using namespace std;

class VideoProcessor
{
    public:
        VideoProcessor() : callIt(true), delay(0), fnumber(0), stop(false), frameToStop(-1) {}
        virtual ~VideoProcessor();

        // set the callback function that
        // will be called for each frame
        void setFrameProcessor(void (*frameProcessingCallback)(cv::Mat&, cv::Mat&));

        // set the instance of the class that
        // implements the FrameProcessor interface
        void setFrameProcessor(FrameProcessor* frameProcessorPtr);

        // set the name of the video file
        bool setInput(std::string filename);

        // to display the processed frames
        void displayInput(std::string wn);

        // to display the processed frames
        void displayOutput(std::string wn);

        // do not display the processed frames
        void dontDisplay();

        // to grab (and process) the frames of the sequence
        void run();
        // Stop the processing
        void stopIt();

        // Is the process stopped?
        bool isStopped();

        // Is a capture device opened?
        bool isOpened();

        // set a delay between each frame
        // 0 means wait at each frame
        // negative means no delay
        void setDelay(int d);


        // process callback to be called
        void callProcess();

        // do not call process callback
        void dontCallProcess();

        void stopAtFrameNo(long frame);

        // return the frame number of the next frame
        long getFrameNumber();

        // set the vector of input images
        bool setInput(const std::vector<std::string>& imgs);


        // set the output video file
        // by default the same parameters than
        // input video will be used
        bool setOutput(const std::string &filename, int codec=0, double framerate=0.0, bool isColor=true);

        // set the output as a series of image files
        // extension must be ".jpg", ".bmp" ...
        bool setOutput(const std::string &filename, const std::string &ext, int numberOfDigits=3, int startIndex=0);

        // get the codec of input video
        int getCodec(char codec[4]);

        // Get the frame rate
        double getFrameRate();

        //Get the frame size
        cv::Size getFrameSize();

    protected:
    private:
        // the OpenCV video capture object
        cv::VideoCapture capture;

        // the callback function to be called
        // for the processing of each frame
        void (*process)(cv::Mat&, cv::Mat&);

        FrameProcessor* frameProcessor;

        // a bool to determine if the
        // process callback will be called
        bool callIt;

        // Input display window name
        std::string windowNameInput;

        // Output display window name
        std::string windowNameOutput;

        // delay between each frame processing
        int delay;

        // number of processed frames
        long fnumber;

        // stop at this frame number
        long frameToStop;

        // to stop the processing
        bool stop;

        // vector of image filename to be used as input
        std::vector<std::string> images;
        // image vector iterator
        std::vector<std::string>::const_iterator itImg;

        // the OpenCV video writer object
        cv::VideoWriter writer;
        // output filename
        std::string outputFile;
        // current index for output images
        int currentIndex;
        // number of digits in output image filename
        int digits;
        // extension of output images
        std::string extension;


        // to get the next frame
        // could be: video file or camera
        bool readNextFrame(cv::Mat& frame);

        // to write the output frame
        // could be: video file or images
        void writeNextFrame(cv::Mat& frame);

};

#endif // VIDEOPROCESSOR_H
