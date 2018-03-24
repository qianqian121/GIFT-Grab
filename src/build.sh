#!/bin/bash -x

mkdir build
cd build
cmake .. -DUSE_FILES=ON -DUSE_HEVC=ON -DENABLE_NONFREE=ON -DUSE_NVENC=ON:hardware-accelerated -DBUILD_TESTS=ON -DBUILD_PYTHON=ON
make -j
make test
