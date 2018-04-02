#!/usr/bin/python

'''
Python test FFMPEG file reader grab video frame then imshow
Example command:
./test_file_imshow.py --file=/mnt/Video/ffmpeg.mp4
'''

from __future__ import absolute_import, division, print_function

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

def main():
    filename = get_args()
    print(filename)

if __name__ == '__main__':
    main()
