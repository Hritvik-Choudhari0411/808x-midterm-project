/**
 * @file humantracker.hpp
 * @author Kshitij Karnawat (@KshitijKarnawat)
 * @author Hritvik Choudhari (hac@umd.edu)
 * @brief HumanTracker class header file.
 * @version 0.1
 * @date 2023-10-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <vector>
#include <memory>
#include <iostream>

#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>

#include "detector.hpp"

namespace acme {

/**
 * @brief Class for tracking humans in video frames.
 */
class HumanTracker {
 public:
    /**
     * @brief Constructor for the Human Tracker class.
     * 
     * @param conf The confidence threshold for filtering out detections.
     */
  explicit HumanTracker(double conf);

  /**
   * @brief Destructor for the Human Tracker class.
   */
  ~HumanTracker();

  /**
     * @brief Track objects (humans) present in a video frame.
     * 
     * @param frame The input video frame.
     * @return A vector of bounding boxes (Rect) representing the tracked objects.
     */
  std::vector<cv::Rect> Trackobj(const cv::Mat &frame);

 private:
  /**
     * @brief Initializes default parameters.
     * 
     * Sets the confidence threshold to filter out detections.
     * 
     * @param conf The confidence threshold.
     */
  void InitParam(double conf);

  /**
     * @brief Filters out detections using a confidence threshold.
     * 
     * @param detections Unfiltered detections from the Detector.
     */
  void ProcessNoise(const std::vector<acme::Detection>& detections);

 private:
  double conf_thresh_;   // Confidence threshold for detection filtering
  std::vector<cv::Rect> objects_;   // Bounding boxes of detected objects
  std::unique_ptr<acme::Detector> detector_;   // Pointer to a Detector object for object detection
};
}  // namespace acme