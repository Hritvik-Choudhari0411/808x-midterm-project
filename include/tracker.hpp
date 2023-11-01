/**
 * @file tracker.hpp
 * @author Kshitij Karanwat (@KshitijKarnawat)
 * @author Hritvik Choudhari (@Hritvik-Choudhari0411)
 * @brief Class for tracking humans in a video.
 * @version 0.1
 * @date 2023-11-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <algorithm>
#include <string>
#include <iostream>
#include <ostream>
#include <vector>

#include <opencv2/opencv.hpp>

namespace acme{
/**
 * @brief Class for tracking humans in a video.
 * 
 */
class Tracker{
 private:
  const float SCORE_THRESHOLD = 0.5;
  const float NMS_THRESHOLD = 0.45;
  const float CONFIDENCE_THRESHOLD = 0.45;

 public:

  /**
   * @brief Display the labels on the frame.
   * 
   * @param frame 
   * @param label 
   * @param top 
   * @param left 
   */
  void DisplayLabels(const cv::Mat &frame, std::string label,
                  int top, int left);

  /**
   * @brief Draw the bounding boxes on the frame.
   * 
   * @param frame 
   * @param detections 
   * @param person 
   * @return cv::Mat 
   */
  cv::Mat DrawBoxes(cv::Mat frame,
                       std::vector<cv::Mat> detections,
                       std::vector<std::string> person);

  /**
   * @brief Detect the humans in the frame.
   * 
   * @param frame 
   * @param model 
   * @return std::vector<cv::Mat> 
   */
  std::vector<cv::Mat> DetectNN(cv::Mat frame, cv::dnn::Net model);
};
}
