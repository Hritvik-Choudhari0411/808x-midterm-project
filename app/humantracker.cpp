/**
 * @file detector.hpp
 * @author Kshitij Karnawat (@KshitijKarnawat)
 * @author Hritvik Choudhari (hac@umd.edu)
 * @brief Human Tracker class source file.
 * @version 0.1
 * @date 2023-10-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
#include "humantracker.hpp"
#include <opencv2/opencv.hpp>


acme::HumanTracker::HumanTracker(double confidence) {
    // Constructor to initialize a HumanTracker object with default parameters
    InitParams(confidence);
}

acme::HumanTracker::~HumanTracker() {}
    // Destructor
void acme::HumanTracker::InitParam(double conf) {
    // Initialize parameters used by the HumanTracker class
    // Set the confidence threshold value to filter out detections
    conf_thresh_ = conf;

    // Set the confidence threshold for the detector object
    double detector_conf(0.2);

    // Set the classes to detect by the Detector
    std::vector<std::string> classes{"person"};

    // Create a Detector class object with the specified configuration
    detector_ = std::make_unique<acme::Detector>(detector_conf, classes);

    // Clear the vector that will store the detected objects
    objects_.clear();
}

std::vector<cv::Rect> acme::HumanTracker::Trackobj(const cv::Mat &frame) {
    // Detect and track objects in the input frame
    // Clear the vector that stores detections
    objects_.clear();

    // Obtain a vector of Detection objects by running the Detector on the frame
    std::vector<acme::Detections> output = detector_->Detections(frame);

    // Filter out the detections to retain those with confidence above the threshold
    ProcessNoise(output);
    // Return the vector of tracked human objects
    return objects_;
}

void acme::HumanTracker::ProcessNoise(const std::vector<acme::Detection>& detections) {
    // Filter and process the detections based on confidence threshold
    for ( acme::Detections detection : detections ) {
        if (detection.conf >= conf_thresh_) {
            // Store the detection only if the detected confidence is above the threshold
            objects_.push_back(detection.bounding_box);
        }
    }
}