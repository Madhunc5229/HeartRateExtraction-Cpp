/**
 * @file CalHeartRate.cpp
 * @author Madhu Narra Chittibabu (madhunc117@gmail.com)
 * @brief This file has all the implementation of CalHeartRate class
 * @version 0.1
 * @date 2023-07-21
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "CalHeartRate.hpp"
/**
 * @brief This method extracts green channel from the video
 *
 * @param greenSignal output (returns the greenchannel values)
 * @param showPreview To show the preview of the forehead
 */
void CalHeartRate::extractGreenChannel(cv::Mat &greenSignal, const bool &showPreview)
{
    cv::VideoCapture cap(_videoPath);

    _fps = cap.get(cv::CAP_PROP_FPS);
    _numFrames = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT));

    while (cap.isOpened())
    {
        // Declare a variable to store the current frame.
        cv::Mat frame;
        cap >> frame;
        // If it's empty, break out of the loop.
        if (frame.empty())
            break;

        cv::Mat foreheadFrame = frame(_foreheadRoI);
        cv::cuda::GpuMat gpu_frame;
        gpu_frame.upload(frame);
        // Extract the green channel
        cv::Mat greenChannel;
        cv::extractChannel(foreheadFrame, greenChannel, 1);

        // Calculate the mean value of the green channel
        double greenValue = cv::mean(greenChannel)[0];
        greenSignal.push_back(greenValue);

        if (showPreview)
        {
            cv::imshow("Forehead ROI", foreheadFrame);
            if (cv::waitKey(1) == 27) // Press 'Esc' key to exit the loop
                break;
        }
    }
}

/**
 * @brief This method computes heart rate from the greenchannel values
 *
 * @param greenSignal Input (List of greenchannel Values)
 * @param heartRate Output (Heart rate in BPM)
 */
void CalHeartRate::extractHeartRate(cv::Mat &greenSignal, double &heartRate)
{
    // Create a complex-valued matrix from the green signal and merge it with an empty matrix to form a 2-channel matrix
    cv::Mat planes[] = {cv::Mat_<float>(greenSignal), cv::Mat::zeros(greenSignal.size(), CV_32F)};
    cv::Mat complexI;
    cv::merge(planes, 2, complexI);

    // Perform Discrete Fourier Transform (DFT) on the complex-valued matrix
    cv::dft(complexI, complexI, cv::DFT_COMPLEX_OUTPUT);

    // Split the complex-valued matrix into its real and imaginary parts
    cv::split(complexI, planes);
    // Calculate the magnitude of the complex numbers
    cv::magnitude(planes[0], planes[1], planes[0]);
    cv::Mat mag = planes[0];

    cv::Mat freqs;
    fftFreqs(freqs);
    cv::Rect firstHalf(0, 0, 1, int(mag.size().height / 2));

    // Taking only the values corresponding to positive frequencies
    mag = mag(firstHalf);

    // convert signal a& frequency to vectors as both are 1D
    std::vector<float> psd(mag.begin<double>(), mag.end<double>());
    std::vector<float> positive_freqs(freqs.begin<double>(), freqs.end<double>());

    // Define the minimum and maximum heart rate values in Hz
    double minHeartRate = 40.0 / 60.0;
    double maxHeartRate = 200.0 / 60.0;

    int max_peak_index = -1;
    double max_mag = 0;

    // Iterate through all positive frequency values and find the peak within the specified heart rate range
    for (int i = 0; i < positive_freqs.size(); i++)
    {
        if (positive_freqs[i] >= minHeartRate && positive_freqs[i] <= maxHeartRate)
        {
            double peak = psd[i];
            if (peak > max_mag)
            {
                max_mag = peak;
                max_peak_index = i;
            }
        }
    }

    // If a peak within the specified heart rate range is found, calculate the heart rate and store it
    // Otherwise, set 'heartRate' to -1, indicating failure to find a suitable peak within the specified range
    (max_peak_index != -1) ? heartRate = positive_freqs.at(max_peak_index) * 60 : heartRate = -1;
}

/**
 * @brief This method computes he sample frequencies from fps and numFrames
 *
 * @param freqs Return the Discrete Fourier Transform sample frequencies.
 */
void CalHeartRate::fftFreqs(cv::Mat &freqs)
{
    // Create the frequency matrix with the appropriate size.
    freqs.create(1, _numFrames / 2, CV_64F);
    double freqResolution = _fps / _numFrames;
    for (int i = 0; i <= _numFrames / 2; ++i)
    {
        freqs.at<double>(i) = i * freqResolution;
    }
}
