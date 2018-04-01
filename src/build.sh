#!/bin/bash -x

mkdir build
cd build
#cmake .. -DUSE_FILES=ON -DUSE_HEVC=ON -DENABLE_NONFREE=ON -DUSE_NVENC=ON:hardware-accelerated -DUSE_PIXELINK_SDK=ON -DBUILD_TESTS=ON -DBUILD_PYTHON=ON
#cmake .. -DUSE_FILES=ON -DUSE_HEVC=ON -DENABLE_NONFREE=ON -DUSE_NVENC=ON -DUSE_PIXELINK_SDK=ON -DBUILD_TESTS=ON -DBUILD_PYTHON=ON -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -DUSE_XVID=ON
cmake .. -DUSE_FILES=ON -DUSE_HEVC=ON -DENABLE_GPL=ON -DUSE_X265=ON -DUSE_PIXELINK_SDK=ON -DBUILD_TESTS=ON -DBUILD_PYTHON=ON -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -DUSE_XVID=ON

make -j
make test
