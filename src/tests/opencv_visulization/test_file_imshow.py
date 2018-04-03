#!/usr/bin/python

'''
Python test FFMPEG file reader grab video frame then imshow
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
from pytest import mark, yield_fixture
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

class MyProcNode(IObservableObserver):
    def __init__(self):
        super(MyProcNode, self).__init__()
    def update(self, frame):
        # Implement gg::IObserver::update(frame)
        data_np = frame.data()
        cv2.imshow('img', data_np)
        cv2.waitKey()

def test_file_to_imshow(filename):
    proc_node = MyProcNode()
    global factory
    file_reader = factory.create_file_reader(
        filename, ColourSpace.BGRA
    )
    file_reader.attach(proc_node)
    time.sleep(20)
    file_reader.detach(proc_node)

def main():
    filename = get_args()
    print(filename)
    test_file_to_imshow(filename)

if __name__ == '__main__':
    main()
