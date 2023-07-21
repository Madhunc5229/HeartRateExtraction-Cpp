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
 - GPU (CUDA 11.0)
## OpenCV 4.6.0 build error with CUDA 12.2 
![cuda_build_error](https://github.com/Madhunc5229/HeartRateExtraction-Cpp/assets/61328094/f118fec0-cd2c-4e9c-80d3-173639615228)

#### Currently OpenCV 4.x version does not build with cuda 12.x versions
 - Link to the issue: https://stackoverflow.com/questions/74830272/build-opencv-with-cuda-12-undefined-identifiers-cudaunbindtexture-texturerefer
 - One possible solution is downgrading my cuda version to 11.x but that is not compatible with my current linux drivers and my display drivers will stop working.

<!-- ## Building the package
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
- Set the `showPreview` flag to `true` in the `extractGreenChannel()` function -->
