/**
 * @file CalHeartRate.hpp
 * @author Madhu Narra Chittibabu (madhunc117@gmail.com)
 * @brief This is file contains all the definitions to compute Heart Rate
 * @version 0.1
 * @date 2023-07-21
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef CAL_HEART_RATE_H
#define CAL_HEART_RATE_H

#include <iostream>
#include <opencv2/opencv.hpp>

/**
 * @brief This class has methods & attributes to compute Heart Rate from video
 *
 */
class CalHeartRate
{

public:
    /**
     * @brief Construct a new Cal Heart Rate object
     *
     * @param videoPath path to the video file
     * @param foreheadRoI forehead region
     */
    CalHeartRate(const std::string &videoPath, const cv::Rect &foreheadRoI) : _videoPath(videoPath), _foreheadRoI(foreheadRoI) {}

    /**
     * @brief This method extracts green channel from the video
     *
     * @param greenSignal output (returns the greenchannel values)
     * @param showPreview To show the preview of the forehead
     */
    void extractGreenChannel(cv::Mat &greenSignal, const bool &showPreview = false);

    /**
     * @brief This method computes heart rate from the greenchannel values
     *
     * @param greenSignal Input (List of greenchannel Values)
     * @param heartRate Output (Heart rate in BPM)
     */
    void extractHeartRate(cv::Mat &greenSignal, double &heartRate);

private:
    /**
     * @brief total number of frames in the video
     *
     */
    int _numFrames;
    /**
     * @brief Frames per second in the video
     *
     */
    double _fps;
    /**
     * @brief file path for the video
     *
     */
    const std::string _videoPath;
    /**
     * @brief forehead region of the frame
     *
     */
    const cv::Rect _foreheadRoI;
    /**
     * @brief This method computes he sample frequencies from fps and numFrames
     *
     * @param freqs Return the Discrete Fourier Transform sample frequencies.
     */
    void fftFreqs(cv::Mat &freqs);
};

#endif