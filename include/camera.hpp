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

#include <humantracker.hpp>

namespace acme {
     /**
      * @brief Enumerates the different modes in which the program can run.
      *
      */
  enum Mode {
      Training, ///< Collect Training Data
      Testing, ///< Run Detector on user-specified test data and generate metrics
      RealTimeImp = 0 ///< Run the Full Human Detector and Tracker module
  };

/**
 * @brief Acme Robotics Human Detection and Tracking Module
 * 
 * This module can run in different modes as required by the user. It outputs
 * the location of humans in the robot's reference frame.
 */
class Camera {
 public:
    /**
     * @brief Constructor for the Camera class.
     * 
     * Initializes default parameters used by the Camera class.
     * 
     * @param cam_id The camera identifier.
     * @param calibration_factor The calibration factor for the camera.
     */
      explicit Camera(const int cam_id = 0, double calibration_factor = -1);

    /**
     * @brief Destructor for the Camera class.
     */
      ~Camera();

    /**
     * @brief Main function of the Camera class to start the program.
     * 
     * The behavior of the program changes based on the selected mode.
     * It can run the Human Detector and Tracker, collect training data, or
     * perform detection on test data and produce metrics.
     * 
     * @param mode The mode in which the program should run.
     */
      void Run(const acme::Mode mode);

    /**
     * @brief Set the Robot Pose in (x, y, z) coordinates.
     * 
     * @param rob_pose The robot's pose.
     */
      void FixPoseRobot(const acme::Pose &rob_pose);

    /**
     * @brief Set the Camera Pose in (x, y, z) coordinates with respect to the robot's pose.
     * 
     * @param camera_pose The camera's pose.
     */
      void FixPoseCamera(const acme::Pose &camera_pose);

    /**
     * @brief Set the focal length of the camera.
     * 
     * @param focal_length The focal length of the camera.
     */
      void FixFocus(double focal_length);

     /**
      * @brief Set the Processing Size 
      * 
      * @param w 
      * @param h 
      */
      void FixResolution(const int w, const int h);

    /**
     * @brief Set the processing size.
     * 
     * @param w The width of the processing frame.
     * @param h The height of the processing frame.
     */
      void FixResolution(const cv::Size & res);

    /**
     * @brief Set the average object size.
     * 
     * @param avg_obj_h The average size of the object.
     */
      void FixObjHeight(const double avg_obj_h);

    /**
     * @brief Set whether to display a window for visualization.
     * 
     * @param display Set to true to display a window for visualization.
     */
      void Display(const bool display);

    /**
     * @brief Set the test counter for testing purposes.
     * 
     * If the test counter is set to a value greater than -1, the program will run
     * for that many frames only.
     * 
     * @param counter The test counter.
     */
      void Counter(const int counter);

    /**
     * @brief Get the detected objects (humans in this case) in the robot's reference frame.
     * 
     * @return A vector of objects in the robot's reference frame.
     */
      std::vector<acme::Pose> GetDetObj();

 private:
    /**
     * @brief When the mode is Training, the Run method will call CollectTrainData.
     * 
     * This function:
     * - Asks the user to input the output directory.
     * - Asks the user how many images to save.
     * - Asks the user for the frame interval.
     */
      void GetTrainDataset();

    /**
     * @brief When the mode is Testing, the Run method will call GetTestDataset.
     * 
     * This function:
     * - Asks the user to input the test data directory.
     * - The test data should be in YOLO format.
     * - Runs the detector on the test images.
     * - Calculates the average Intersection over Union (IoU) by comparing with ground truth.
     * - Displays the metric output.
     */
      void GetTestDataset();

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

    /**
     * @brief Calculate the calibration factor.
     * 
     * Uses resolution, focal length, and a test subject in the real world to calibrate
     * the camera. The calibration factor is used to convert human positions from pixels
     * to the robot's reference frame.
     */
      void CalibrateCamera();

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