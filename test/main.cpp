/**
 * @file main.cpp
 * @author Kshitij Karnawat (@KshitijKarnawat)
 * @author Hritvik Choudhary (hac@umd.edu)
 * @brief Main file for testing. Initializes the test suite.
 * @version 0.1
 * @date 2023-10-24
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <gtest/gtest.h>

#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
