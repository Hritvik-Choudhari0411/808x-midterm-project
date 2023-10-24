/**
 * @file humantracker.hpp
 * @author Kshitij Karnawat (@KshitijKarnawat)
 * @author Hritvik Choudhary (hac@umd.edu)
 * @brief HumanTracker class header file.
 * @version 0.1
 * @date 2023-10-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <iostream>
#include <vector>

#include "detector.hpp"
#include "camera.hpp"
#include "utils.hpp"

namespace acme {
    /**
     * @brief Class for Tracking Humans in a video.
     * 
     */
    class HumanTracker{
        private:

        /**
         * @brief Construct a new HumanTracker object
         * 
         */
        HumanTracker();

        /**
         * @brief Destroy the HumanTracker object
         * 
         */
        ~HumanTracker();


        unsigned int human_counter_;
        Detector detector_;
        Camera camera_;

        public:
        
        /**
         * @brief Track humans in a video.
         * 
         */
        void TrackHuman();

        /**
         * @brief Detect humans in a video.
         * 
         */
        void DetectHuman();


    };
}