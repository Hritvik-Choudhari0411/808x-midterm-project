/**
 * @file detector.hpp
 * @author Kshitij Karnawat (@KshitijKarnawat)
 * @author Hritvik Choudhary (hac@umd.edu)
 * @brief Detector class header file.
 * @version 0.1
 * @date 2023-10-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

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
		 */
		Detector();

		/**
		 * @brief Destroy the Detector object
		 * 
		 */
		~Detector();

		cv::Mat frame_;
		std::vector<std::string> classes_;
		std::vector<cv::Rect> bounding_boxes_;

		public:
		/**
		 * @brief Detect humans in a frame.
		 * 
		 * @param frame 
		 * @return std::vector<cv::Rect> 
		 */
		std::vector<cv::Rect> Detect(cv::Mat frame);

		/**
		 * @brief Function to Load the YOLOv8 model.
		 * 
		 */
		void LoadModel();
		
		
  };
}