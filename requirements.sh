sudo add-apt-repository 'deb http://security.ubuntu.com/ubuntu xenial-security main'
sudo apt update
sudo apt-get install build-essential checkinstall cmake pkg-config yasm gfortran git
sudo apt-get install libjpeg8-dev libjasper-dev libpng12-dev
sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev
sudo apt-get install libxine2-dev libv4l-dev
sudo apt-get install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev
sudo apt-get install libqt4-dev libgtk2.0-dev libtbb-dev
sudo apt-get install libatlas-base-dev
sudo apt-get install libfaac-dev libmp3lame-dev libtheora-dev
sudo apt-get install libvorbis-dev libxvidcore-dev
sudo apt-get install libopencore-amrnb-dev libopencore-amrwb-dev
sudo apt-get install x264 v4l-utils

### Download the test video file
cd data
wget --no-check-certificate 'https://docs.google.com/uc?export=download&id=1ewMg0YxcMLCDdaD3gSGZ5uDlV5l1TMQg' -O test.mov

### Download the model weights file
wget https://github.com/AlexeyAB/darknet/releases/download/darknet_yolo_v4_pre/yolov4-tiny.weights
cd ..

### For opencv
sudo apt-get install libopencv-dev

#eigen 
sudo apt install libeigen3-dev