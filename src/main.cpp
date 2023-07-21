#include "CalHeartRate.hpp"

int main()
{   
    cv::cuda::setDevice(1);
    const std::string video_path = "../data/codingtest.mov";
    cv::cuda::GpuMat gpu_greenChannelVlaues;
    cv::Rect foreheadROI(340, 140, 240, 100);
    
    CalHeartRate chr(video_path, foreheadROI);

    cv::Mat greenchannelValues;
    gpu_greenChannelVlaues.upload(greenchannelValues);
    chr.extractGreenChannel(greenchannelValues);

    double heartRate;
    chr.extractHeartRate(greenchannelValues, heartRate);

    std::cout << "Estimated Heart Rate: " << heartRate << "BPM\n";

    return 0;
}