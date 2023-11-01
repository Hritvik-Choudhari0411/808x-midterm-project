/**
 * @file main.cpp
 * @author Kshitij Karnawat (@KshitijKarnawat)
 * @author Hritvik Chaudhari (hac@umd.edu)
 * @brief main file for the project
 * @version 0.1
 * @date 2023-10-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <opencv2/opencv.hpp>

#include "../include/tracker.hpp"

int main() {
  acme::Tracker tracker;

  std::vector<std::string> class_list;
  class_list.push_back("person");

  cv::VideoCapture cap(0);
  cv::Mat frame;

  while (true) {
    cap.read(frame);

    cv::dnn::Net model;
    model = cv::dnn::readNet("../model/yolov7-tiny.onnx");

    std::vector<cv::Mat> detections;
    detections = tracker.DetectNN(frame, model);

    cv::Mat img = tracker.DrawBoxes(frame.clone(), detections, class_list);

    cv::imshow("Output", img);
    char key = cv::waitKey(1);
    if (key == 27) {
      break;
    }
  }

  cap.release();
  cv::destroyAllWindows();
  return 0;
}
