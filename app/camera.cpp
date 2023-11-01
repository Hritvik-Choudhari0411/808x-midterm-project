/**
 * @file camera.cpp
 * @author Kshitij Karnawat (@KshitijKarnawat)
 * @author Hritvik Choudhari (hac@umd.edu)
 * @brief Camera class source file.
 * @version 0.1
 * @date 2023-10-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <eigen3/Eigen/Dense>
#include <opencv2/opencv.hpp>

#include "camera.hpp"
#include "utils.hpp"

acme::Utils utils;

acme::Camera::Camera(const int cam_id, double calibration_factor) {
    // Constructor for the Camera class, initializes default parameters.
    InitParam(cam_id, calibration_factor);
}

acme::Camera::~Camera() {}

void acme::Camera::RunLive() {
    // if calib_factor == default value, calculate calib_factor

    // setup the display window name
    const std::string win_name = "Display";

    if ( display_ ) {
        // create a display window if show window is true
        cv::namedWindow(win_name, cv::WINDOW_FREERATIO);
    }

    // initialize a variable to store frame counter with 0
    int frame_counter = 0;

    // initialize an empty vector to store bounding boxes
    std::vector<cv::Rect> obj_tracks{};

    // create a variable to store the source frame size
    cv::Size src_size;

    // run an indefinite loop to read video stream
    while (true) {
        // create a variable to store the source video frame
        cv::Mat src_frame;
        if ( cap_.read(src_frame) ) {
            if ( frame_counter == 0 ) {
                // calculate the source frame size once
                src_size = src_frame.size();
            }

            // resize src frame according to processing size
            processing_frame_ = utils.ResizeImage(src_frame, processing_size_);

            // get bboxes of objects tracked by HumanTracker class in frame
            obj_tracks = human_tracker_->Trackobj(processing_frame_);

            // draw bboxes on the frame
            //  processing_frame_ = Utils::DrawBbox(processing_frame_, obj_tracks);

            // convert the bboxes from img plane to robot ref frame
            ToRobotRefFrame(obj_tracks);

            // resize process frame back to src frame size
            processing_frame_ = utils.ResizeImage(processing_frame_, src_size);

            if ( display_ ) {
                // if show window is true, display the current video frame
                cv::imshow(win_name, processing_frame_);
                char k = cv::waitKey(1);
                if ( k == 27 || k == 'q' ) {
                    // EXIT if user hits 'Esc' or 'q' on the keyboard
                    return;
                }
            }

            // increment the frame counter
            frame_counter++;

            // for Testing purpose only, run the loop for test_counter times
            // if ( counter_ != -1 ) {
            //     if ( frame_counter > counter_ ) {
            //         return;
            //     }
            // }
        } else {
            std::cout << "no more frames" << std::endl;
            return;
        }
    }
}

void acme::Camera::InitParam(int camera_id, double calib_factor) {
    // set camera id
    camera_id_ = camera_id;

    // set calib_factor default value
    calib_factor_ = calib_factor;

    objects_in_frame_.clear();

    // set focal length in meters default value
    focal_length_ = 0.036;

    // set human height, in meters default value
    avg_obj_h_ = 1.7;

    // set processing size default value
    processing_size_ = cv::Size(640, 480);

    // set confidence threshold for human_tracker default value
    double conf_threshold = 0.6;

    // initialize HumanTracker Object
    human_tracker_ = std::make_unique<acme::HumanTracker>(conf_threshold);

    // set show window default value
    display_ = true;

    // set test counter default value
    counter_ = -1;

    // open camera stream using the video capture object
    // Uncomment the line below if using webcam
    auto path = camera_id_;

    // Path for testing on a video; comment this line if using webcam
    // auto path = "../data/test.mp4";
    cap_.open(path);

    // check if camera is open
    if ( cap_.isOpened() ) {
        // set srouce frame width
        frame_w_ = cap_.get(cv::CAP_PROP_FRAME_WIDTH);

        // set srouce frame height
        frame_h_ = cap_.get(cv::CAP_PROP_FRAME_HEIGHT);

        // set srouce frame rate
        frame_rate_ = cap_.get(cv::CAP_PROP_FPS);

        // if height or width is 0, throw error
        if (frame_h_ == 0 || frame_w_ == 0) {
            // Display error msg and EXIT
            std::cout << "Empty frame" << std::endl;
            return;
        }
    } else {
            // Display error msg and EXIT
            std::cout << "Unable to open camera" << std::endl;
            return;
    }

    // initialize robot pose
    robot_pose_ = acme::Pose(7, 5, 8);

    // initialize camera pose
    camera_pose_ = acme::Pose(2, 2, 3);
}

void acme::Camera::ToRobotRefFrame(const std::vector<cv::Rect> &tracks) {
    objects_in_frame_.clear();
    Eigen::Matrix4d transform_mat;
    Eigen::Vector4d obj_in_cam;
    Eigen::Vector4d obj_in_robot;
    // transformation matrix considering
    transform_mat << 1, 0, 0, robot_pose_.x - camera_pose_.x,
                     0, 1, 0, robot_pose_.y - camera_pose_.y,
                     0, 0, 1, robot_pose_.z - camera_pose_.z,
                     0, 0, 0, 1;

    if ( tracks.size() ) {
        // create a variable to store Pose of the detected object
        acme::Pose obj_pose;
        int bound_box_id = 0;
        for ( cv::Rect box : tracks ) {
            bound_box_id++;
            double factor = avg_obj_h_ / box.height;
            // convert from img plane to Pose(x, y, z) using calib_factor
            obj_pose = utils.GetPoseFromPixel(box);
            obj_pose.y = obj_pose.y * factor;
            obj_pose.z = obj_pose.z * factor;

            // from world coordinates to camera coordinates using homogeneous
            // CHECK UTILS GET TRANSFORMED POSE METHOD
            obj_in_cam << obj_pose.x , obj_pose.y, obj_pose.z , 1;
            // convert from camera Pose to Robot Pose
            obj_in_robot = transform_mat * obj_in_cam;

            // store detected obj Pose in a vector
            objects_in_frame_.push_back(acme::Pose(obj_in_robot[0],
                obj_in_robot[1], obj_in_robot[2]));

            std::string label = std::to_string(bound_box_id) + " (" +
                            std::to_string(static_cast<int>(obj_in_robot[0]))
                                + ","+
                            std::to_string(static_cast<int>(obj_in_robot[1]))
                                + ","+
                            std::to_string(static_cast<int>(obj_in_robot[2]))
                                + ")";

            processing_frame_ = utils.DrawBoundingBox(processing_frame_, box);
        }
    }
}