/**
 * @file camera.hpp
 * @author Kshitij Karnawat (@KshitijKarnawat)
 * @author Hritvik Choudhary (hac@umd.edu)
 * @brief Camera class source file.
 * @version 0.1
 * @date 2023-10-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "camera.hpp"

acme::Camera::Camera(){
    video_capture_ = cv::VideoCapture(0);
    camera_location_ = {0, 0};
}

acme::Camera::~Camera(){
    video_capture_.release();
}

cv::Mat acme::Camera::ReadFrame(){
    video_capture_.read(frame_);
    return frame_;
}

void acme::Camera::CalibrateCamera(){
    std::cout << "Calibrating camera..." << std::endl;
}