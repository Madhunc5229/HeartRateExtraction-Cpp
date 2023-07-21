# HeartRateExtraction-Cpp


[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

This is C++ software package which uses OpenCV library to extract heart rate in BPM (Beats per Minute) from a video of a person's face. The pipeline for the project is:
-  Define a Region of Interest (forehead)
-  Extract green channel values for every frame and store it as a signal
-  Perform Fourier Analysis on the green channel signal & extract prominent frequncy
  
 ## Dependencies
 - Linux (Ubuntu 20.04)
 - OpenCV 4.x
 - CMake


## Building the package
- Open a new terminal on your linux system and type the following commands 


#### Clone the repository
```
git clone https://github.com/Madhunc5229/HeartRateExtraction-Cpp.git
```

#### Build and run
```
mkdir build
cd build
cmake ..
./FindHeartRate
```
- You should see the heart rate printed on terminal: "Estimated Heart Rate: XXBPM"

#### To see preview of forehead region
- Set the `showPreview` flag to `true` in the `extractGreenChannel()` function
