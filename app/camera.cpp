/**
 * @file camera.hpp
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

void acme::Camera::Run(const Mode mode) {
    // Based on the selected mode, execute a specific module.
    switch ( static_cast<int>(mode) ) {
        case 1:
            GetTrainDataset();
            break;
        case 2:
            GetTestDataset();
            break;
        default:
            RunLive();
            break;
    }
}


void acme::Camera::FixPoseRobot(const Pose &rob_pose) {
    // Set the robot's pose.
    robot_pose_ = rob_pose;
}

void acme::Camera::FixPoseCamera(const Pose &camera_pose) {
    // Set the camera's pose.
    camera_pose_ = camera_pose;
}

void acme::Camera::FixFocus(const double focal_length) {
    // Set the focal length of the camera.
    focal_length_ = focal_length;
}

void acme::Camera::FixResolution(const int w, const int h) {
    // Set the resolution (width and height) for image processing.
    cv::Size s = cv::Size(w, h);
    FixResolution(s);
}

void acme::Camera::FixResolution(const cv::Size &res) {
    // Set the image processing resolution.
    processing_size_ = res;
}

void acme::Camera::FixObjHeight(const double avg_obj_h) {
    // Set the average object height.
    avg_obj_h_ = avg_obj_h;
}

void acme::Camera::Display(const bool show_window) {
    // Enable or disable the display window.
    display_ = show_window;
}

void acme::Camera::Counter(const int counter) {
    // Set a counter for controlling the number of frames to process.
    counter_ = counter;
}

std::vector<acme::Pose> acme::Camera::GetDetObj() {
    // Get a vector of detected object poses in the current frame.
    return objects_in_frame_;
}


void acme::Camera::GetTrainDataset() {
    std::string address;
    // Capture a training dataset, save frames, and compute object bounding boxes.
    int frame_count = 0;
    // Get the address to save captured frames and the number of frames to capture.

    /// Uncommnent the lines below while running in training mode
    /// std::cout << "Enter the full path to save frames" << std::endl;
    /// std::getline(std::cin, address);

    /// comment the line below when running in training mode
    address = "../data/train/";

    /// Uncommnent the lines below while running in training mode
    /// Get number of frames to be captured
    /// std::cout << "Enter frame count" << std::endl;
    /// std::cin >> frame_count;

    /// comment the line below when running in training mode
    frame_count = 2;
    cv::VideoCapture cap(camera_id_);

  if (!cap.isOpened()) {
    std::cerr << "ERROR: Unable to open video " << std::endl;
    return;
  } else {
        for (int counter = 0; counter < frame_count; counter++) {
    cv::Mat frame;
    cap >> frame;
    std::string file_name = address+"//"+std::to_string(counter) + ".jpg";
    cv::imwrite(file_name, frame);
  }
}

  return;
}


void acme::Camera::GetTestDataset() {

    // acme::Utils utils;
    // Load images for testing, ground truth, and evaluate object detection.
    cap_.release();
    cv::Mat img_1 = cv::imread("../data/test/1.png");
    cv::Mat img_2 = cv::imread("../data/test/2.png");
    cv::Mat img_3 = cv::imread("../data/test/3.png");
    cv::Mat img_4 = cv::imread("../data/test/4.png");
    cv::Mat img_5 = cv::imread("../data/test/5.jpeg");

    // Load test images and ground truth data.
    /// ground truth for img 2
    std::vector<cv::Rect> gt_2 = {cv::Rect(330, 107, 160, 294)};

    /// ground truth for img 3
    std::vector<cv::Rect> gt_3 = {cv::Rect(298, 126, 98, 228)};

    /// ground truth for img 1
    std::vector<cv::Rect> gt_1 = {cv::Rect(300, 21, 197, 310)};

    /// ground truth for img 4
    std::vector<cv::Rect> gt_4 = {cv::Rect(297, 84, 147, 265)};

    /// ground truth for img 4
    std::vector<cv::Rect> gt_5 = {cv::Rect(320, 55, 110, 400),
        cv::Rect(430, 50, 120, 415)};
    std::vector<std::vector<cv::Rect>> gt_list = {gt_1, gt_2,
        gt_3, gt_4, gt_5};

    // For each image, perform object tracking and evaluate with ground truth.
    std::vector <cv::Mat> image_list = {img_1, img_2, img_3, img_4, img_5};
    for (int i = 0; i < static_cast<int>(image_list.size()); i++) {
        processing_frame_ = utils.ResizeImage(image_list[i], processing_size_);

        /// get bboxes of objects tracked by HumanTracker class in frame
        auto bound_box = human_tracker_->Trackobj(processing_frame_);
        for ( int j = 0; j < static_cast<int>(gt_list[i].size()); j++ ) {
        double iou = utils.CalculateIoU(gt_list[i][j], bound_box[j]);
        std::cout << " IoU score:" << iou << std::endl;
        /// Uncomment this block when using Testing mode
        /*
        cv::rectangle ( processing_frame_, gt_list[i][j], cv::Scalar(0,255,0), 2 );
        cv::rectangle ( processing_frame_, bound_box[j], cv::Scalar(0,0,255), 2 );

        std::string label1 = "ID: " + std::to_string(j);
        std::string label2 = "IoU: " + std::to_string(static_cast<float>(iou));

        cv::putText(processing_frame_, label1, cv::Point(gt_list[i][j].x,
            gt_list[i][j].y), 0, 0.5, cv::Scalar(255,255,255), 4);
        cv::putText(processing_frame_, label1, cv::Point(gt_list[i][j].x,
            gt_list[i][j].y), 0, 0.5, cv::Scalar(255,0,0), 2);

        cv::putText( processing_frame_, label2, cv::Point(gt_list[i][j].x,
            gt_list[i][j].y+20), 0, 0.5, cv::Scalar(255,255,255), 4);
        cv::putText (processing_frame_, label2, cv::Point(gt_list[i][j].x,
            gt_list[i][j].y+20), 0, 0.5, cv::Scalar(255,0,0), 2);*/
    }

        /// Uncomment this line when in Testing mode

        /*
        cv::imshow("img", processing_frame_);
        cv::waitKey(0);*/
    }
}



void acme::Camera::RunLive() {
    /// if calib_factor == default value, calculate calib_factor
    if (calib_factor_ == -1) {
        CalibrateCamera();
    }

    /// setup the display window name
    const std::string win_name = "Display";

    if ( display_ ) {
        /// create a display window if show window is true
        cv::namedWindow(win_name, cv::WINDOW_FREERATIO);
    }

    /// initialize a variable to store frame counter with 0
    unsigned int frame_counter = 0;

    /// initialize an empty vector to store bounding boxes
    std::vector<cv::Rect> obj_tracks{};

    /// create a variable to store the source frame size
    cv::Size src_size;

    /// run an indefinite loop to read video stream
    while (true) {
        /// create a variable to store the source video frame
        cv::Mat src_frame;
        if ( cap_.read(src_frame) ) {
            if ( frame_counter == 0 ) {
                /// calculate the source frame size once
                src_size = src_frame.size();
            }

            /// resize src frame according to processing size
            processing_frame_ = utils.ResizeImage(src_frame, processing_size_);

            /// get bboxes of objects tracked by HumanTracker class in frame
            obj_tracks = human_tracker_->Trackobj(processing_frame_);

            /// draw bboxes on the frame
            //  processing_frame_ = Utils::DrawBbox(processing_frame_, obj_tracks);

            /// convert the bboxes from img plane to robot ref frame
            ToRobotRefFrame(obj_tracks);

            /// resize process frame back to src frame size
            processing_frame_ = utils.ResizeImage(processing_frame_, src_size);

            if ( display_ ) {
                /// if show window is true, display the current video frame
                cv::imshow(win_name, processing_frame_);
                char k = cv::waitKey(1);
                if ( k == 27 || k == 'q' ) {
                    /// EXIT if user hits 'Esc' or 'q' on the keyboard
                    return;
                }
            }

            /// increment the frame counter
            frame_counter++;

            /// for Testing purpose only, run the loop for test_counter times
            if ( counter_ != -1 ) {
                if ( static_cast<int>(frame_counter) > counter_ ) {
                    return;
                }
            }
        } else {
            std::cout << "Unable to read frame" << std::endl;
            return;
        }
    }
}

void acme::Camera::CalibrateCamera() {
    /// calculate calib factor and focal length here
    cv::Mat image = cv::imread("..//data//Calibration.jpg", 0);
    cv::Mat thresh;
    /// original distance between object and camera
    double original_distance = 20;
    /// original width of the object
    double original_width = 10;
    /// thresholding the image
    cv::threshold(image, thresh, 150, 255, cv::THRESH_BINARY);
    /// variable tostore contours
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    /// search for the contour
    cv::findContours(thresh, contours, hierarchy,
                    cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    double maxArea = 0;
    int max_cont_area_id = -1;
    /// get ID for contour of maximum area
    for (int j = 0; j < static_cast<int>(contours.size()); j++) {
        double newArea = cv::contourArea(contours.at(j));
        if (newArea > maxArea) {
            maxArea = newArea;
            max_cont_area_id = j;
        }
    }
    /// make bounding box
    cv::Rect box = cv::boundingRect(contours[max_cont_area_id]);
    /// calculate focal length
    double focalLength = (box.width * original_distance) / original_width;
    std::cout << focalLength;
    /// set focal length
    FixFocus(focalLength);
    calib_factor_ = focalLength * avg_obj_h_;
}



void acme::Camera::InitParam(int camera_id, double calib_factor) {
    /// set camera id
    camera_id_ = camera_id;

    /// set calib_factor default value
    calib_factor_ = calib_factor;

    objects_in_frame_.clear();

    /// set focal length in meters default value
    focal_length_ = 0.036;

    /// set human height, in meters default value
    avg_obj_h_ = 1.7;

    /// set processing size default value
    processing_size_ = cv::Size(640, 480);

    /// set confidence threshold for human_tracker default value
    double conf_threshold = 0.6;

    /// initialize HumanTracker Object
    human_tracker_ = std::make_unique<acme::HumanTracker>(conf_threshold);

    /// set show window default value
    display_ = true;

    /// set test counter default value
    counter_ = -1;

    /// open camera stream using the video capture object
    /// Uncomment the line below if using webcam
    /// auto path = camera_id_;

    /// Path for testing on a video; comment this line if using webcam
    auto test_path = "..//data//test.mov";
    cap_.open(test_path);

    /// check if camera is open
    if ( cap_.isOpened() ) {
        /// set srouce frame width
        frame_w_ = cap_.get(cv::CAP_PROP_FRAME_WIDTH);

        /// set srouce frame height
        frame_h_ = cap_.get(cv::CAP_PROP_FRAME_HEIGHT);

        // set srouce frame rate
        frame_rate_ = cap_.get(cv::CAP_PROP_FPS);

        /// if height or width is 0, throw error
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
    /// transformation matrix considering
    transform_mat << 1, 0, 0, robot_pose_.x - camera_pose_.x,
                     0, 1, 0, robot_pose_.y - camera_pose_.y,
                     0, 0, 1, robot_pose_.z - camera_pose_.z,
                     0, 0, 0, 1;

    if ( tracks.size() ) {
        /// create a variable to store Pose of the detected object
        acme::Pose obj_pose;
        int bound_box_id = 0;
        for ( cv::Rect box : tracks ) {
            bound_box_id++;
            double factor = avg_obj_h_ / box.height;
            /// convert from img plane to Pose(x, y, z) using calib_factor
            obj_pose = utils.GetPoseFromPixel(box);
            obj_pose.y = obj_pose.y * factor;
            obj_pose.z = obj_pose.z * factor;

            // from world coordinates to camera coordinates using homogeneous
            // CHECK UTILS GET TRANSFORMED POSE METHOD
            obj_in_cam << obj_pose.x , obj_pose.y, obj_pose.z , 1;
            /// convert from camera Pose to Robot Pose
            obj_in_robot = transform_mat * obj_in_cam;

            /// store detected obj Pose in a vector
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