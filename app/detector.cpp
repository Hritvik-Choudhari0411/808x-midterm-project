/**
 * @file detector.hpp
 * @author Kshitij Karnawat (@KshitijKarnawat)
 * @author Hritvik Choudhary (hac@umd.edu)
 * @brief Detector class header file.
 * @version 0.1
 * @date 2023-10-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "detector.hpp"

acme::Detector::Detector(double confidence_threshold_, std::vector<std::string> &classes_){

}

acme::Detector::~Detector(){

}


void acme::Detector::InitModel(int backend, int target){

}

std::vector<cv::Rect> acme::Detector::Detect(cv::Mat& frame){
    return frame;
}

void acme::Detector::SetClasses(std::vector<std::string> &classes){

}

void acme::Detector::SetNMSThreshold(double nms_threshold){

}


void acme::Detector::SetInputWidth(double input_width){

}

void acme::Detector::SetInputHeight(double input_height){

}

void acme::Detector::SetSwapRB(bool swap_rb){

}

void acme::Detector::CropImage(bool crop_img){

}

void acme::Detector::SetBackend(int backend){

}

void acme::Detector::SetTarget(int target){

}

void acme::Detector::SetNumChannels(int num_channels){
    
}
