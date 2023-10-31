/**
 * @file main.cpp
 * @author Kshitij Karnawat (@KshitijKarnawat)
 * @author Hritvik Chaudhari (hac@umd.edu)
 * @brief main file for the project
 * @version 0.1
 * @date 2023-10-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <camera.hpp>

int main() {
    /// define on which mode the module has to operate
    acme::Mode mode = acme::Mode::Training;

    /// initialize Camera class object with camera id and calib factor
    acme::Camera ACME_robot(0, 0.5);

    /// call Run method with the selected mode of operation
    ACME_robot.Run(mode);

    /// print a success message if module exited without any error
    std::cout << "Successfully Created Acme Human Tracker robot" << std::endl;
    return 0;
}