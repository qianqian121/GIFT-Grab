#!/usr/bin/python

'''
Python test FFMPEG file reader grab video frame then write using opencv
Example command:
./test_file_imshow.py --file=/mnt/Video/ffmpeg.mp4
'''

from __future__ import absolute_import, division, print_function
from pygiftgrab import IObservableObserver
from pygiftgrab import VideoTargetFactory
from pygiftgrab import Codec
from pygiftgrab import ColourSpace
from pygiftgrab import VideoSourceFactory
import numpy as np
import cv2
import time
import os
import os.path
# from pytest import mark, yield_fixture
import scipy.ndimage as ndimage
import argparse

__author__ = ''


def get_args():
    '''This function parses and return arguments passed in'''
    # Assign description to the help doc
    parser = argparse.ArgumentParser(
        description='Python Script test FFMPEG file reader grab video frame then imshow')
    # Add arguments
    parser.add_argument(
        '-f', '--filename', type=str, help='file full path and name', required=True)
    # Array for all arguments passed to script
    args = parser.parse_args()
    # Assign args to variables
    filename = args.filename
    # Return all variable values
    return filename

def test_file_to_imshow(filename):
    factory_source = VideoSourceFactory.get_instance()
    file_reader = factory_source.create_file_reader(
        filename, ColourSpace.BGRA
    )
    factory_target = VideoTargetFactory.get_instance()
    file_writer = factory_target.create_file_writer(Codec.Xvid,
                                                    'opencv_output_py.avi',
                                                    30)
    file_reader.attach(file_writer)
    time.sleep(20)
    file_reader.detach(file_writer)

def main():
    filename = get_args()
    print(filename)
    test_file_to_imshow(filename)

if __name__ == '__main__':
    main()
