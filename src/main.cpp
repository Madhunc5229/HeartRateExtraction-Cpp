#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>
// #include <opencv2/core.hpp>
// #include <opencv2/videoio.hpp>
// #include<opencv2/imgproc/imgproc.hpp>
// #include <opencv2/highgui.hpp>
// #include <iostream>
// #include <stdio.h>
using namespace std;
using namespace cv;

int main()
{
    // Read the video file
    VideoCapture cap("../data/codingtest.mov", 0);

    if (!cap.isOpened())
    {
        cout << "Error opening video file" << endl;
        return -1;
    }
    double fps = cap.get(CAP_PROP_FPS);
    int frame_width = static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH));
    int frame_height = static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT));
    int top_left_width = 340;
    int top_left_height = 140;
    int bbox_width = 240;
    int bbox_height = 100;

    Rect forehead_roi(top_left_width, top_left_height, bbox_width, bbox_height);


    while (cap.isOpened())
    {
        Mat frame;
        cap >> frame;

        if (frame.empty())
            break;
        frame = frame(forehead_roi);
        Mat different_channels[3];
        split(frame, different_channels);
        Mat g = different_channels[1];
        // int rows = frame.rows;
        // int cols = frame.cols;
        // cout << "frame height: \n"
        //      << rows << "\n frame width: " << cols << "\n";
        imwrite("frame_g.jpg", g);
        break;
    }
    cap.release();
}

// // Variables for video properties

// double fps = cap.get(CAP_PROP_FPS);
// int num_frames = static_cast<int>(cap.get(CAP_PROP_FRAME_COUNT));

// // Region of Interest (ROI) for forehead area (you can adjust this based on your video)
// Rect forehead_roi(0, frame_height / 4, frame_width, frame_height / 6);

// // Variables for Fourier analysis
// int fourier_length = num_frames;
// Mat signal(fourier_length, 1, CV_32FC1);
// float* signal_data = signal.ptr<float>(0);

// // Read and process each frame of the video
// for (int frame_num = 0; frame_num < num_frames; frame_num++) {
//     Mat frame;
//     cap >> frame;

//     if (frame.empty()) {
//         cout << "End of video" << endl;
//         break;
//     }

//     // Convert frame to green channel (the heart rate is strongest in the green channel)
//     Mat green_channel;
//     cvtColor(frame, green_channel, COLOR_BGR2GRAY);

//     // Extract the ROI for forehead area
//     Mat forehead_roi_frame = green_channel(forehead_roi);

//     // Average the pixels over the forehead area
//     Scalar forehead_avg = mean(forehead_roi_frame);

//     // Store the average value in the signal for Fourier analysis
//     signal_data[frame_num] = forehead_avg.val[0];
// }

// // Perform Fourier analysis on the signal
// Mat fourier_result;
// dft(signal, fourier_result, DFT_COMPLEX_OUTPUT);
// split(fourier_result, { fourier_result, Mat() });
// magnitude(fourier_result, fourier_result);

// // Find the peak in the power spectral density (PSD) to extract the heart rate
// double minVal, maxVal;
// Point minLoc, maxLoc;
// minMaxLoc(fourier_result, &minVal, &maxVal, &minLoc, &maxLoc);

// // Calculate the heart rate (in beats per minute, assuming 30 fps for the video)
// double heart_rate = (maxLoc.y * fps) / fourier_length * 60.0;

// cout << "Extracted Heart Rate: " << heart_rate << " BPM" << endl;
