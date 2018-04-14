#!/bin/bash -x

mkdir build
cd build
export PKG_CONFIG_PATH="/opt/ffmpeg/lib/pkgconfig:$PKG_CONFIG_PATH"
#cmake .. -DUSE_FILES=ON -DUSE_HEVC=ON -DENABLE_NONFREE=ON -DUSE_NVENC=ON:hardware-accelerated -DUSE_PIXELINK_SDK=ON -DBUILD_TESTS=ON -DBUILD_PYTHON=ON
#cmake .. -DUSE_FILES=ON -DUSE_HEVC=ON -DENABLE_NONFREE=ON -DUSE_NVENC=ON -DUSE_PIXELINK_SDK=ON -DBUILD_TESTS=ON -DUSE_NUMPY=ON -DBUILD_PYTHON=ON -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -DUSE_XVID=ON
cmake .. -DUSE_FILES=ON -DUSE_HEVC=ON -DENABLE_GPL=ON -DUSE_X265=ON -DUSE_PIXELINK_SDK=ON -DBUILD_TESTS=ON -DBUILD_PYTHON=ON -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -DUSE_XVID=ON

make -j
make test

# before run python test. copy pygiftgrab.so to tests/xxx/
export PYTHONPATH=/home/dev/project/github/GIFT-Grab/src/tests:/home/dev/project/github/GIFT-Grab/src/python/modules:/home/dev/project/github/GIFT-Grab/src/build:$PYTHONPATH

#boost.numpy package
git clone https://github.com/ndarray/Boost.NumPy.git
cd Boost.Numpy
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3 10
mkdir build
cd build
cmake ..
make -j
make install
sudo mv /usr/local/include/boost/numpy* /opt/boost/include/boost/
sudo mv /usr/local/lib64/libboost_numpy.so /opt/boost/lib/