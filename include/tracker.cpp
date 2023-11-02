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
  cv::Size class_label =
      cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.65, 1, 0);
  top = cv::max(top, class_label.height);

  cv::Point top_corner = cv::Point(left, top);  // cv::Point(x,y)

  cv::Point bottom_corner =
      cv::Point(left + class_label.width, top + class_label.height);

  cv::rectangle(frame, top_corner, bottom_corner, cv::Scalar(0, 0, 0),
                cv::FILLED);

  cv::putText(frame, label, cv::Point(left, top + class_label.height),
              cv::FONT_HERSHEY_SIMPLEX, 0.65, cv::Scalar(255, 255, 255), 1);
}

cv::Mat acme::Tracker::DrawBoxes(cv::Mat frame, std::vector<cv::Mat> detections,
                                 std::vector<std::string> person) {
  std::vector<int> class_ids;
  std::vector<float> confidence_list;
  std::vector<cv::Rect> bounding_boxes;

  int x = frame.cols / 640;
  int y = frame.rows / 640;

  // ptr to ptr conversion
  float *data = reinterpret_cast<float *>(detections[0].data);

  const int pixels = 25200;  // 25200 = 3 * 640 * 640 / 16

  for (int i = 0; i < pixels; ++i) {
    float confidence = data[4];
    if (confidence >= CONFIDENCE_THRESHOLD) {
      float *classes_scores =
          data + 5;  // Class scores start from index 5 for each detection.

      cv::Mat scores(1, person.size(), CV_32FC1, classes_scores);

      cv::Point class_id;
      double max_class_score;
      minMaxLoc(scores, 0, &max_class_score, 0, &class_id);

      if (max_class_score > SCORE_THRESHOLD) {
        confidence_list.push_back(confidence);
        class_ids.push_back(class_id.x);

        float cx = data[0];
        float cy = data[1];

        float width = data[2];
        float height = data[3];

        int box_left = (cx - 0.5 * width) * x;
        int box_top = (cy - 0.5 * height) * y;
        int box_width = width * x;
        int box_height = height * y;

        bounding_boxes.push_back(
            cv::Rect(box_left, box_top, box_width, box_height));
      }
    }

    data += 85;  // Skip to next detection.
  }

  std::vector<int> nms_boxes;
  cv::dnn::NMSBoxes(bounding_boxes, confidence_list, SCORE_THRESHOLD,
                    NMS_THRESHOLD, nms_boxes);
  for (unsigned int i = 0; i < nms_boxes.size(); i++) {
    int idx = nms_boxes[i];
    cv::Rect box = bounding_boxes[idx];

    int box_left = box.x;
    int box_top = box.y;
    int box_width = box.width;
    int box_height = box.height;

    rectangle(frame, cv::Point(box_left, box_top),
              cv::Point(box_left + box_width, box_top + box_height),
              cv::Scalar(0, 255, 0), 3);

    std::string label;  // = cv::format("%.2f", confidence_list[idx]);
    label =
        person[class_ids[idx]] + ":" + cv::format("%.2f", confidence_list[idx]);

    acme::Tracker::DisplayLabels(frame, label, box_top, box_left);
  }
  return frame;
}

std::vector<cv::Mat> acme::Tracker::DetectNN(cv::Mat frame,
                                             cv::dnn::Net model) {
  cv::Mat blob;
  cv::dnn::blobFromImage(frame, blob, 1. / 255., cv::Size(640, 640),
                         cv::Scalar(), true, false);

  model.setInput(blob);

  std::vector<cv::Mat> detections;
  model.forward(detections, model.getUnconnectedOutLayersNames());

  return detections;
}
