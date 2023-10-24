/**
 * @file detector.hpp
 * @author Kshitij Karnawat (@KshitijKarnawat)
 * @author Hritvik Choudhary (hac@umd.edu)
 * @brief Human Tracker class source file.
 * @version 0.1
 * @date 2023-10-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include <vector>
#include <opencv2/opencv.hpp>

#include "humantracker.hpp"

acme::HumanTracker::HumanTracker(double confidence_){
    
}

acme::HumanTracker::~HumanTracker(){

}

void acme::HumanTracker::InitParams(double confidence){

}

void acme::HumanTracker::ProcessFrame(cv::Mat &frame){

}

std::vector<cv::Rect> acme::HumanTracker::TrackHuman(cv::Mat &frame){
    std::vector<cv::Rect> humans;
    return humans;
}
