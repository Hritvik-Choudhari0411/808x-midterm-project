/**
 * @file camera.hpp
 * @author Kshitij Karnawat (@KshitijKarnawat)
 * @author Hritvik Choudhari (hac@umd.edu)
 * @brief Camera class header file.
 * @version 0.1
 * @date 2023-10-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <opencv2/opencv.hpp>


#include "humantracker.hpp"

namespace acme {

  /**
  * @brief Acme Robotics Human Detection and Tracking Module
  * 
  * This module can run in different modes as required by the user. It outputs
  * the location of humans in the robot's reference frame.
  */
  class Camera{
    public:
      /**
      * @brief Constructor for the Camera class.
      * 
      * Initializes default parameters used by the Camera class.
      * 
      * @param cam_id The camera identifier.
      * @param calibration_factor The calibration factor for the camera.
      */
      // Camera();

      Camera(const int cam_id = 0, double calibration_factor = -1);

      /**
      * @brief Destructor for the Camera class.
      */
      ~Camera();

        /**
        * @brief When mode is RealTimeImp, Run Method will call RunLive
        * 
        * perform calibration if not calibration_factor not set
        * Resizes the source frame according to processing size
        * Get human tracks by calling TrackHumans method of class HumanTracker
        * Call DrawBbox to draw bbox on the processing frame
        * Call ToRobotRefFrame to convert bbox from image plane to robot ref frame
        * if display_ is true, display the processing frame
        * 
        */
      void RunLive();

  private:
      /**
      * @brief Converts bounding boxes from the image plane to the robot's reference frame.
      * 
      * Uses the calibration factor, robot pose, and camera pose to transform the bounding box
      * locations.
      * 
      * @param tracks A vector of bounding boxes.
      */
      void ToRobotRefFrame(const std::vector<cv::Rect> &tracks);

      /**
      * @brief Initializes parameters for the Camera class.
      * 
      * - Sets default values for camera ID, calibration factor, focal length, average human height,
      *   frame width, frame height, frame rate, processing size, confidence threshold for the HumanTracker object.
      * - Initializes the HumanTracker object with the confidence threshold.
      * - Opens the camera with the specified camera ID.
      * - Sets default values for showing the window and test counter.
      * 
      * @param cam_id The camera identifier.
      * @param calibration_factor The calibration factor for the camera.
      */
      void InitParam(int cam_id, double calibration_factor);

    private:
      int camera_id_;
      double focal_length_;
      int frame_w_;
      int frame_h_;
      int frame_rate_;
      double avg_obj_h_;
      cv::Mat processing_frame_;
      cv::Size processing_size_;
      double calib_factor_;
      acme::Pose robot_pose_;
      acme::Pose camera_pose_;
      std::vector<acme::Pose> objects_in_frame_;
      std::unique_ptr<acme::HumanTracker> human_tracker_;
      cv::VideoCapture cap_;
      bool display_;
      int counter_;
  };
}  // namespace acme