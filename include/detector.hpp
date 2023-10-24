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

#include <algorithm>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

#include "camera.hpp"
#include "utils.hpp"

namespace acme {

  /**
   * @brief Detector class for detecting humans in a frame.
   * 
   */
	class Detector{
		private:
		/**
		 * @brief Construct a new Detector object
		 * 
		 * @param confidence_threshold confidence threshold for the model.
		 * @param classes_ classes to detect for the model.
		 */
		Detector(double confidence_threshold_, std::vector<std::string> &classes_);

		/**
		 * @brief Destroy the Detector object
		 * 
		 */
		~Detector();

		double confidence_threshold_;
		double nms_threshold_;
		double input_width_;
		double input_height_;
		bool swap_rb_;
		bool crop_img_;
		int backend_;
		int target_;
		int num_channels_;
		std::unique_ptr<cv::dnn::Net> network_;
		cv::Mat frame_;
		std::vector<std::string> classes_;
		std::vector<cv::Rect> bounding_boxes_;

		void InitModel(int backend, int target);

		public:
		/**
		 * @brief Detect humans in a frame.
		 * 
		 * @param frame 
		 * @return std::vector<cv::Rect> 
		 */
		std::vector<cv::Rect> Detect(cv::Mat& frame);

		/**
		 * @brief Set the Classes object for detection
		 * 
		 * @param classes 
		 */
		void SetClasses(std::vector<std::string> &classes);

		/**
		 * @brief Setter for NMS threshold.
		 * 
		 * @param nms_threshold 
		 */
		void SetNMSThreshold(double nms_threshold);

		/**
		 * @brief Set the Input Width Object
		 * 
		 * @param input_width 
		 */
		void SetInputWidth(double input_width);

		/**
		 * @brief Set the Input Height object
		 * 
		 * @param input_height 
		 */
		void SetInputHeight(double input_height);

		/**
		 * @brief Set the Swap R B object
		 * 
		 * @param swap_rb 
		 */
		void SetSwapRB(bool swap_rb);

		/**
		 * @brief get the Cropped Image object
		 * 
		 * @param crop_img 
		 */
		void CropImage(bool crop_img);

		/**
		 * @brief Set the Backend object
		 * 
		 * @param backend 
		 */
		void SetBackend(int backend);

		/**
		 * @brief Set the Target object
		 * 
		 * @param target 
		 */
		void SetTarget(int target);

		/**
		 * @brief Set the Num Channels object
		 * 
		 * @param num_channels 
		 */
		void SetNumChannels(int num_channels);
		
		
  };
}