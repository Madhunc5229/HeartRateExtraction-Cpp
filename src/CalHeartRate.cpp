#include "CalHeartRate.hpp"

void CalHeartRate::extractGreenChannel(cv::Mat &greenSignal, const bool &showPreview){
    cv::VideoCapture cap(_videoPath);

    _fps = cap.get(cv::CAP_PROP_FPS);
    _numFrames = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT));


    while (cap.isOpened())
    {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty())
            break;

        cv::Mat foreheadFrame = frame(_foreheadRoI);
        cv::Mat greenChannel;
        cv::extractChannel(foreheadFrame, greenChannel, 1); // Green channel is the second channel (0-indexed)

        double greenValue = cv::mean(greenChannel)[0];
        greenSignal.push_back(greenValue);

        if (showPreview){
            cv::imshow("Forehead ROI", foreheadFrame);
            if (cv::waitKey(1) == 27) // Press 'Esc' key to exit the loop
                break;
        }
        
    }

}

void CalHeartRate::fftFreqs(cv::Mat &freqs){
    freqs.create(1, _numFrames / 2, CV_64F);
    double freqResolution = _fps / _numFrames;
    for (int i = 0; i <= _numFrames / 2; ++i)
    {
        freqs.at<double>(i) = i * freqResolution;
    }
}

void CalHeartRate::extractHeartRate(cv::Mat &greenSignal, double &heartRate){

    cv::Mat planes[] = {cv::Mat_<float>(greenSignal), cv::Mat::zeros(greenSignal.size(), CV_32F)};
    cv::Mat complexI;
    cv::merge(planes, 2, complexI);

    cv::dft(complexI, complexI, cv::DFT_COMPLEX_OUTPUT); // Fourier Transform

    cv::split(complexI, planes);
    cv::magnitude(planes[0], planes[1], planes[0]);
    cv::Mat mag = planes[0];
    int numFrames = greenSignal.rows;

    cv::Mat freqs;
    fftFreqs(freqs);
    cv::Rect firstHalf(0, 0, 1, 911);

    // taking the first half
    mag = mag(firstHalf);

    std::vector<float> psd(mag.begin<double>(), mag.end<double>());
    std::vector<float> positive_freqs(freqs.begin<double>(), freqs.end<double>());

    double minHeartRate = 40.0 / 60.0; // Convert BPM to Hz
    double maxHeartRate = 200.0 / 60.0;

    int max_peak_index = -1;
    double max_mag = 0;

    std::vector<int> indicesInRange;

    for (int i = 0; i < positive_freqs.size(); i++) {
        if (positive_freqs[i] >= minHeartRate && positive_freqs[i] <= maxHeartRate) {
            double peak = psd[i];
            if (peak > max_mag) {
                max_mag = peak;
                max_peak_index = i;
            }
        }
    }

    (max_peak_index != -1) ? heartRate =  positive_freqs.at(max_peak_index) * 60 : heartRate = -1;

}
