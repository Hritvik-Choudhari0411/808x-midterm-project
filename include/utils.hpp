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
  Pose(){
    x = 0;
    y = 0;
    z = 0;
  }

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
   * @brief Transform the pose from source to target.
   *
   * @param pose_src
   * @param pose_tgt
   * @return Pose
   */
  Pose TransformPose(Pose pose_src, Pose pose_tgt);

  /**
   * @brief Calculate the IoU between two bounding boxes.
   *
   * @param bounding_box1
   * @param bounding_box2
   * @return float
   */
  float CalculateIoU(cv::Rect bounding_box1, cv::Rect bounding_box2);

  /**
   * @brief Get the Bounding Box object
   *
   * @param image
   * @return cv::Rect
   */
  cv::Rect GetBoundingBox();

  /**
   * @brief Draw the bounding box on the image.
   *
   * @param image
   * @param bounding_box
   * @return cv::Mat
   */
  cv::Mat DrawBoundingBox(cv::Mat image, cv::Rect bounding_box);

  /**
   * @brief Get the Bounding Box Center object
   *
   * @param bounding_box
   * @return cv::Point
   */
  cv::Point GetBoundingBoxCenter(cv::Rect bounding_box);

  /**
   * @brief Get the Pose From Pixel object
   *
   * @param bounding_box
   * @return Pose
   */
  Pose GetPoseFromPixel(cv::Rect bounding_box);
};
}  // namespace acme