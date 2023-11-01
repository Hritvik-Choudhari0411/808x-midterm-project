/**
 * @file test.cpp
 * @author Kshitij Karnawat (@KshitijKarnawat)
 * @author Hritvik Choudhari (hac@umd.edu)
 * @brief Test file for the project.
 * @version 0.1
 * @date 2023-10-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <gtest/gtest.h>
#include <string>

#include <opencv2/dnn/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>


#include "../include/tracker.hpp"

TEST(test, test) {
  cv::Mat image = cv::imread("model/test.jpg");
  acme::Tracker tracker;
  std::string label = "person";
  int top = 10;
  int left = 10;
  ASSERT_NO_THROW(tracker.DisplayLabels(image, label, top, left));
}
