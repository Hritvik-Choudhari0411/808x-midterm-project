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

#include <iostream>
#include <memory>
#include <vector>

#include "include/detector.hpp"

namespace acme {
/**
 * @brief Class for Tracking Humans in a video.
 *
 */
class HumanTracker {
 private:
  /**
   * @brief Construct a new HumanTracker object
   *
   */
  explicit HumanTracker(double confidence_);

  /**
   * @brief Destroy the HumanTracker object
   *
   */
  ~HumanTracker();

  unsigned int human_counter_;
  double confidence_;

  std::unique_ptr<acme::Detector> detector_;

  /**
   * @brief Initialize the parameters for the tracker.
   *
   * @param confidence
   */
  void InitParams(double confidence);

  /**
   * @brief Process the frame to detect humans.
   *
   * @param frame
   */
  void ProcessFrame(cv::Mat frame);

 public:
  /**
   * @brief Track humans in a frame.
   *
   * @param frame
   * @return std::vector<cv::Rect>
   */
  std::vector<cv::Rect> TrackHuman(cv::Mat frame);
};
}  // namespace acme
