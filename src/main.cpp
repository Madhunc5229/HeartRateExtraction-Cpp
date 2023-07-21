#include "CalHeartRate.hpp"

int main()
{
    const std::string video_path = "../data/codingtest.mov";
    cv::Rect foreheadROI(340, 140, 240, 100);

    CalHeartRate chr(video_path, foreheadROI);

    cv::Mat greenchannelValues;
    chr.extractGreenChannel(greenchannelValues);

    double heartRate;
    chr.extractHeartRate(greenchannelValues, heartRate);

    std::cout << "Estimated Heart Rate: " << heartRate << "BPM\n";

    return 0;
}