# 808x-midterm-project

![CICD Workflow status](https://github.com/KshitijKarnawat/808x-midterm-project/actions/workflows/main.yml/badge.svg)
[![codecov](https://codecov.io/gh/KshitijKarnawat/808x-midterm-project/branch/devel/graph/badge.svg)](https://codecov.io/gh/KshitijKarnawat/808x-midterm-project)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

## Project Overview

Human (N>=1) obstacle detector and tracker (tracker does not need to handle occlusion).  Module must output location info directly usable in a robot's reference frame. Assume the use of only one monocular video camera.

## Dependencies

- OpenCV 4.7.* or higher
- CMake 3.2 or higher
- Ubuntu 18.04 or higher
- GoogleTest (for testing)

## Installation & Building

### [Intalling OpenCV](https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html)

```sh
# Install minimal prerequisites (Ubuntu 18.04 as reference)
sudo apt update && sudo apt install -y cmake g++ wget unzip

# Download and unpack sources
wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/4.x.zip

unzip opencv.zip
unzip opencv_contrib.zip

# Create build directory and switch into it
mkdir -p build && cd build

# Configure
cmake -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib-4.x/modules ../opencv-4.x

# Build
cmake --build .
```

## UML Diagrams

![UML Diagram](./etc/UML%20DIagrams/Class_UML_Diagram.png)

## Quad Chart

![Quad Chart](./etc/quad_chart.png)

## Proposal Video

[![Proposal Video](https://i9.ytimg.com/vi_webp/stZ0M5cbaZc/mq1.webp?sqp=CNyAvKkG-oaymwEmCMACELQB8quKqQMa8AEB-AH-CYAC0AWKAgwIABABGEwgXyhlMA8=&rs=AOn4CLDdHdtkntw7L618R1pgjqB7f9HwSw)](https://www.youtube.com/watch?v=stZ0M5cbaZc&ab_channel=KshitijKarnawat)
