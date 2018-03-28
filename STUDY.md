export OpenCV_DIR=/opt/opencv

SET(OpenCV_LIBS -L/opt/opencv/lib ${OpenCV_LIBS}

cmake .. -DUSE_FILES=ON -DUSE_HEVC=ON -DENABLE_NONFREE=ON -DUSE_NVENC=ON:hardware-accelerated -DBUILD_TESTS=ON -DBUILD_PYTHON=ON -DUSE_XVID=ON
