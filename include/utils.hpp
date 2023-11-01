/**
 * @file utils.hpp
 * @author Kshitij Karnawat (@KshitijKarnawat)
 * @author Hritvik Choudhari (hac@umd.edu)
 * @brief Utility functions header file.
 * @version 0.1
 * @date 2023-10-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once
#include <vector>
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

namespace acme {

/**
 * @brief Pose structure to store the pose of the object.
 *
 */
struct Pose {
  /**
   * @brief Construct a new Pose object
   * 
   */
  Pose(){
    x = 0;
    y = 0;
    z = 0;
  }

  /**
   * @brief Construct a new Pose object
   * 
   * @param x1 
   * @param y1 
   * @param z1 
   */
  Pose(float x1, float y1, float z1) {
    x = x1;
    y = y1;
    z = z1;
  }

  float x;
  float y;
  float z;
};

/**
 * @brief Utils class to store the utility functions.
 *
 */
class Utils {
 public:
  /**
   * @brief Resize the image to the given size.
   *
   * @param image
   * @param size
   * @return cv::Mat
   */
  cv::Mat ResizeImage(cv::Mat image, cv::Size size);


  /**
   * @brief Draw the bounding box on the image.
   *
   * @param image
   * @param bounding_box
   * @return cv::Mat
   */
  cv::Mat DrawBoundingBox(cv::Mat image, const cv::Rect& bounding_box, const std::string& l);

  /**
   * @brief Get the Bounding Box Center object
   * 
   * @param bbox 
   * @return cv::Point 
   */
  cv::Point GetBoundingBoxCenter(const cv::Rect &bbox);


  /**
   * @brief Get the Pose From Pixel object
   *
   * @param bounding_box
   * @return Pose
   */
  acme::Pose GetPoseFromPixel(cv::Rect bounding_box, double calib_factor);

};
}  // namespace acme