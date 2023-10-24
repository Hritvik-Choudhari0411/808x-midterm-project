/**
 * @file utils.hpp
 * @author Kshitij Karnawat (@KshitijKarnawat)
 * @author Hritvik Choudhary (hac@umd.edu)
 * @brief Utility functions header file.
 * @version 0.1
 * @date 2023-10-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

namespace acme {
    class Utils{
        public:
       
       /**
        * @brief Resize the image.
        * 
        */
         void ResizeImage();

        /**
         * @brief Transform pose to world coordinates.
         * 
         */
            void TransformPose();

        /**
         * @brief Calculate the IoU.
         * 
         */
        void CalculateIoU();

        /**
         * @brief Get the bounding boxes for a human.
         * 
         */
        void GetBoundingBox();

        /**
         * @brief Draw the bounding boxes on the frame.
         * 
         */
        void DrawBoundingBox();


    };
}