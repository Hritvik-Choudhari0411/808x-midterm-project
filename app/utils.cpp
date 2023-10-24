/**
 * @file detector.hpp
 * @author Kshitij Karnawat (@KshitijKarnawat)
 * @author Hritvik Choudhary (hac@umd.edu)
 * @brief Utils class source file.
 * @version 0.1
 * @date 2023-10-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "utils.hpp"
#include "opencv2/core/types.hpp"

cv::Mat acme::Utils::ResizeImage(cv::Mat image, cv::Size size){
    return image;
}

acme::Pose acme::Utils::TransformPose(acme::Pose pose_src, acme::Pose pose_tgt){
    return pose_src;
}

float acme::Utils::CalculateIoU(cv::Rect bounding_box1, cv::Rect bounding_box2){
    return 0.0;
}

cv::Rect acme::Utils::GetBoundingBox(){
    return cv::Rect();
}

cv::Mat acme::Utils::DrawBoundingBox(cv::Mat image, cv::Rect bounding_box){
    return image;
}

cv::Point acme::Utils::GetBoundingBoxCenter(cv::Rect bounding_box){
    return cv::Point();
}

acme::Pose acme::Utils::GetPoseFromPixel(cv::Rect bounding_box){
    return acme::Pose();
}