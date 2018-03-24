#!/bin/bash -ex

#sudo apt-get update && sudo apt-get install -y libsdl2-2.0 glade ffmpeg

export PIXELINK_SDK_INC=/home/dev/project/pixelink_sdk/include

export PIXELINK_SDK_LIB=/home/dev/project/pixelink_sdk/lib

export LD_LIBRARY_PATH=$PIXELINK_SDK_LIB:$LD_LIBRARY_PATH

