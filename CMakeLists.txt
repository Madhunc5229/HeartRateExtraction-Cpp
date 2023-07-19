# cmake_minimum_required(VERSION 3.10)

# project(HeartRateExtraction-Cpp)


# find_package(OpenCV REQUIRED)

# set(OPENCV_INCLUDE_DIR /usr/local/include/opencv4/)
# set(OPENCV_LIB_DIR /usr/local/lib/)

cmake_minimum_required(VERSION 2.8)
project( DisplayImage )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( DisplayImage src/main.cpp )
target_link_libraries( DisplayImage ${OpenCV_LIBS} )
# message(STATUS "OpenCV library path: ${OPENCV_LIB_DIR}")

# # set include directory
# target_include_directories(test PUBLIC "${OPENCV_INCLUDE_DIR}")

# # set library directory
# target_link_directories(test PUBLIC "${OPENCV_LIB_DIR}")

# # link specific object files we need
# target_link_libraries(test opencv_imgcodecs opencv_core opencv_imgproc opencv_videoio)