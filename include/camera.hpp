/**
 * @file camera.hpp
 * @author Kshitij Karnawat (@KshitijKarnawat)
 * @author Hritvik Choudhary (hac@umd.edu)
 * @brief Camera class header file.
 * @version 0.1
 * @date 2023-10-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <array>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#include "utils.hpp"

namespace acme {
    /**
     * @brief Class for Camera.
     * 
     */
    class Camera{
        private:

        /**
         * @brief Construct a new Camera object
         * 
         */
        Camera();

        /**
         * @brief Destroy the Camera object
         * 
         */
        ~Camera();
    
        cv::VideoCapture video_capture_;
        cv::Mat frame_;
        std::array<int, 2> camera_location_;

        public:

        /**
         * @brief Get the Frame object
         * 
         * @return cv::Mat 
         */
        cv::Mat ReadFrame();

        /**
         * @brief Calibrate the camera.
         * 
         */
        void CalibrateCamera();

    };
}