FROM ubuntu
WORKDIR /opencv
# Install minimal prerequisites (Ubuntu 18.04 as reference)
RUN apt update && apt install -y cmake g++ wget unzip ninja-build gdb
# Download and unpack sources
RUN wget -O opencv.zip https://github.com/opencv/opencv/archive/master.zip
RUN wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/master.zip
RUN unzip opencv.zip
RUN unzip opencv_contrib.zip
# Create build directory and switch into it
WORKDIR /opencv/build
# Configure
RUN cmake -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib-master/modules -GNinja ../opencv-master
# Build
RUN ninja
ENV OpenCV_DIR /opencv/build
WORKDIR /code
COPY . /code
RUN cmake CMakeLists.txt
RUN make -j 12
