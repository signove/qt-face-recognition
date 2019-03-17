# Open CV Installation

Do the following steps to install openCV on a ubuntu18.04 based OS
- Install the build dependencies
```sh
 sudo apt-get install build-essential
 sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
 sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev
```
  - Download and unzip the opencv sorces
```sh
 mkdir -p ~/opencv_install
 cd ~/opencv_install
 wget -O opencv.zip https://github.com/opencv/opencv/archive/3.4.4.zip
 wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/3.4.4.zip
 unzip opencv.zip
 unzip opencv_contrib.zip
```

  - Build and install 
```sh
 cd opencv-3.4.4
 mkdir build
 cd build
 cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local  .. -D INSTALL_C_EXAMPLES=ON  -D OPENCV_EXTRA_MODULES_PATH=~/opencv_install/opencv_contrib-3.4.4/modules -D BUILD_EXAMPLES=ON ..
 make -j4 #-j4 indicates to usa 4 cores to compile. If you have more processor cores availes you can change this to j6,j8...
 sudo make install
```
Now it's all set. Run the sample app to ensure it is ok, in the opencv_sample folder, enter...
```sh
 cmake .
 make
```
This will generate a binary called FacialFeatures. Run with with the following args
```sh
 ./FacialFeatures foto.jpg face.xml --eyes=eyes.xml
```
