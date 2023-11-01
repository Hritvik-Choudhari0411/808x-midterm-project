/**
 * @file utils.cpp
 * @author Kshitij Karnawat (@KshitijKarnawat)
 * @author Hritvik Choudhari (hac@umd.edu)
 * @brief Utils class source file.
 * @version 0.1
 * @date 2023-10-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "utils.hpp"

#include <opencv2/core/types.hpp>

cv::Mat acme::Utils::ResizeImage(cv::Mat image, cv::Size size) { return image; }

cv::Mat DrawBoundingBox(cv::Mat image, const cv::Rect& bounding_box, const std::string& l){
  // creating a copy of frame
  cv::Mat frame = image.clone();

  // set color for Bbox
  cv::Scalar color = cv::Scalar(0, 0, 255);

  // set color for label x
  cv::Scalar l_color = cv::Scalar::all(255);

  // initialize font type
  int f_face(0);

  // initialize font scale
  double f_scale(1);

  // variable to store label point
  cv::Point l_pt;
  // variable to store label top point
  cv::Point top_pt;
  // variable to store label bottom point
  cv::Point bottom_pt;

  // initialize baseline
  int b_line(0);

  // variable for label size
  cv::Size l_size;

  // draws rectangle on frame
  cv::rectangle(frame, bounding_box, color, 2, cv::LINE_AA);

  // get label size
  l_size = cv::getTextSize(l, f_face, f_scale, 2, &b_line);

  // get top point for label rectangle
  top_pt = cv::Point(bounding_box.x, bounding_box.y);

  // get bottom point for label rectangle
  bottom_pt = cv::Point(bounding_box.x + l_size.width, bounding_box.y+l_size.height);

  //  get point for label
  l_pt = cv::Point(bounding_box.x, bounding_box.y+l_size.height);

  // draw rectangle for label
  cv::rectangle(frame, top_pt, bottom_pt, color, -1, 16);

  // display text of label
  cv::putText(frame, l, l_pt, f_face, f_scale, l_color, 2);
  return frame;
}

acme::Pose acme::Utils::GetPoseFromPixel(cv::Rect bounding_box) {
  return acme::Pose();
}