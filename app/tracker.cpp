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

#include "tracker.hpp"

void acme::Tracker::DisplayLabels(const cv::Mat &frame, std::string label,
                  int top, int left) {

  cv::Size class_label = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX,
                                          0.65, 1, 0);
  top = cv::max(top, class_label.height);

  cv::Point top_corner = cv::Point(left, top);

  cv::Point bottom_corner =
      cv::Point(left + class_label.width, top + class_label.height);

  cv::rectangle(frame, top_corner, bottom_corner, cv::Scalar(0, 0, 0),
                  cv::FILLED);

  cv::putText(frame, label,
              cv::Point(left, top + class_label.height), cv::FONT_HERSHEY_SIMPLEX, 0.65,
              cv::Scalar(255, 255, 255), 1);
}

cv::Mat acme::Tracker::DrawBoxes(cv::Mat frame,
                       std::vector<cv::Mat> detections,
                       std::vector<std::string> person) {
  std::vector<int> class_ids;
  std::vector<float> confidences;
  std::vector<cv::Rect> bounding_boxes;

  int x = frame.cols / 640;
  int y = frame.rows / 640;

  float *data = reinterpret_cast<float *>(detections[0].data);

  const int rows = 25200;

  for (int i = 0; i < rows; ++i) {
    float confidence = data[4];
    if (confidence >= CONFIDENCE_THRESHOLD) {
      float *classes_scores = data + 5;

      cv::Mat scores(1, person.size(), CV_32FC1, classes_scores);

      cv::Point class_id;
      double max_class_score;
      minMaxLoc(scores, 0, &max_class_score, 0, &class_id);

      if (max_class_score > SCORE_THRESHOLD) {
        confidences.push_back(confidence);
        class_ids.push_back(class_id.x);

        float cx = data[0];
        float cy = data[1];

        float box_width = data[2];
        float box_height = data[3];

        int left = (cx - 0.5 * box_width) * x;
        int top = (cy - 0.5 * box_height) * y;
        int width = box_width * x;
        int height = box_height * y;

        bounding_boxes.push_back(cv::Rect(left, top, width, height));
      }
    }

    data += 85;
  }

  std::vector<int> indices;
  cv::dnn::NMSBoxes(bounding_boxes, confidences, SCORE_THRESHOLD, NMS_THRESHOLD,
                    indices);
  for (unsigned int i = 0; i < indices.size(); i++) {
    int idx = indices[i];
    cv::Rect box = bounding_boxes[idx];

    int left = box.x;
    int top = box.y;
    int width = box.width;
    int height = box.height;

    rectangle(frame, cv::Point(left, top),
              cv::Point(left + width, top + height), cv::Scalar(0, 255, 0), 3);

    std::string label = cv::format("%.2f", confidences[idx]);
    label = person[class_ids[idx]] + ":" + label;

    acme::Tracker::DisplayLabels(frame, label, top, left);
  }
  return frame;
}

std::vector<cv::Mat> acme::Tracker::DetectNN(cv::Mat frame, cv::dnn::Net model) {
  cv::Mat blob;
  cv::dnn::blobFromImage(frame, blob, 1. / 255.,
                          cv::Size(640, 640), cv::Scalar(),
                          true, false);

  model.setInput(blob);

  std::vector<cv::Mat> detections;
  model.forward(detections, model.getUnconnectedOutLayersNames());

  return detections;
}
