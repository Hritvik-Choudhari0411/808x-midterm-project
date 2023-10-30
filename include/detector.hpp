/**
 * @file detector.hpp
 * @author Kshitij Karnawat (@KshitijKarnawat)
 * @author Hritvik Choudhari (hac@umd.edu)
 * @brief Detector class header file.
 * @version 0.1
 * @date 2023-10-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once
#include <memory>
#include <vector>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/dnn/shape_utils.hpp>

#include <utils.hpp>


namespace acme {
/**
 * @brief Structure to store detection results.
 */
struct Detections {
      Detections(cv::Rect box, double confidence_threshold_, const std::string &n) :
      bounding_box(box), confidence(confidence_threshold_), name(n) {}
      cv::Rect bounding_box;    // Bounding box coordinates
      double confidence;        // Confidence score
      std::string name;         // Name of the detected object
};


/**
 * @brief Detector class for detecting objects in an image.
 */
class Detector {
 public:
    /**
     * @brief Constructor for the Detector class.
     * 
     * @param confidence_threshold The confidence threshold for detection.
     * @param classes The classes to detect.
     */
    Detector(double confidence_threshold_, const std::vector<std::string> &classes_);

    /**
     * @brief Destructor for the Detector class.
     */
    ~Detector();

      /**
     * @brief Run the detector on an image and output the location of detected objects.
     * 
     * @param frame The input image.
     * @return A vector of Detection objects.
     */
      std::vector<acme::Detections> Detect(const cv::Mat& frame);

      /**
     * @brief Set the classes to be detected by the detector.
     * 
     * @param classes_ A vector of class names.
     */
      void SetClasses(const std::vector<std::string> &classes_ = {});

      /**
     * @brief Set the non-maximum suppression (NMS) threshold for the model network.
     * 
     * @param nms_threshold The NMS threshold.
     */

      void FixNmsThresh(const double nms_threshold);

      /**
       * @brief Set the input width for the model network.
       * 
       * @param input_width The input width.
       */
      void FixInputWidth(const int input_width);

      /**
     * @brief Set the input height for the model network.
     * 
     * @param input_height The input height.
     */
      void FixInputHeight(const int input_height);

      /**
       * @brief Set the scale factor for the model network.
       * 
       * @param scale_factor The scale factor.
       */
      void FixScaleFactor(const double scale_factor);

      /**
       * @brief Set the mean value to subtract for the model network.
       * 
       * @param mean The mean value to subtract.
       */
      void FixMean(const cv::Scalar &mean);

      /**
       * @brief Set whether to swap the Red and Blue channels for the model network.
       * 
       * @param swap_rb Set to true to swap Red and Blue channels.
     */
      void FixSwapRB(const bool swap_rb);

      /**
       * @brief Set whether to crop the image for the model network.
       * 
       * @param crop_img Set to true to enable image cropping.
       */
      void CropImage(const bool crop_img);

      /**
       * @brief Set the backend value for the model network.
       * 
       * @param backend The backend to use.
       */
      void FixBackend(const int backend);

      /**
       * @brief Set the target value for the model network.
       * 
       * @param target The target value.
       */
      void FixTarget(const int target);

      /**
       * @brief Set the number of channels for the model network.
       * 
       * @param num_channels The number of channels.
       */
      void FixNumChannels(const int num_channels);

 private:
      /**
       * @brief Run the model network once when initializing the Detector class.
       */
      void WarmUp();

      /**
       * @brief Initialize default model parameters.
       * 
       * @param confidence_threshold The confidence threshold for detection.
       * @param classes The classes to detect.
       */
      void InitModel(double confidence_threshold_, const std::vector<std::string> classes_);

      /**
       * @brief Process the output of one forward pass by the model network.
       * 
       * @param size The size of the input image.
       * @return A vector of Detection objects.
       */
      std::vector<acme::Detections> ProcessModel(const cv::Size &size);

 private:
    double confidence_threshold_;      // Confidence threshold for detection
    std::vector<std::string> all_classes_; // All available classes
    std::vector<std::string> classes_;    // Classes to detect
    double nms_threshold_;             // Non-maximum suppression threshold
    double input_width_;               // Input width for the model network
    double input_height_;              // Input height for the model network
    cv::Size size_factor;                    // Size of the input image
    double scale_factor;                     // Scale factor for the model network
    cv::Scalar mean_factor;                  // Mean value to subtract
    bool swap_factor;                        // Swap Red and Blue channels
    bool crop_factor;                        // Crop the image
    int backend_;                      // Backend for the model network
    int target_;                       // Target for the model network
    int num_channels_;                 // Number of channels
    cv::dnn::Net model;             // Model network
    std::vector<std::string> layer_outputs; // Output layer names
    std::vector<cv::Mat> model_output;     // Output images from the network
};
}  // namespace acme