#ifndef CAL_HEART_RATE_H
#define CAL_HEART_RATE_H

#include <iostream>
#include <opencv2/opencv.hpp>


class CalHeartRate {

    public:
        CalHeartRate(const std::string &videoPath, const cv::Rect &foreheadRoI) : _videoPath(videoPath), _foreheadRoI(foreheadRoI) {}
        
        void extractGreenChannel(cv::Mat &greenSignal, const bool &showPreview=false);

        void extractHeartRate(cv::Mat &greenSignal, double &heartRate);


    private:
        int _numFrames;
        double _fps;
        const std::string _videoPath;
        const cv::Rect _foreheadRoI;
        void fftFreqs(cv::Mat &freqs);

};

#endif