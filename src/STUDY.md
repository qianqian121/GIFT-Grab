http://www.bogotobogo.com/OpenCV/opencv_3_tutorial_creating_mat_objects.php

Creating Mat objects

Constructor Mat()

We'll learn how we can write a matrix to an image file, however, for debugging purposes it's much more convenient to see the actual values. We do this using the << operator of Mat.

Here is a testing file, t.cpp:

#include <opencv2/core/core.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    Mat img(2,2, CV_8UC3, Scalar(126,0,255));
    cout << "img = \n " << img << "\n\n";
    return 0;
}

and with the cmake file :

cmake_minimum_required(VERSION 2.8)
project( Tutorials )
find_package( OpenCV REQUIRED )
add_executable( Tutorials t.cpp )
target_link_libraries( Tutorials ${OpenCV_LIBS} )

So, put the two files in a directory called Tutorials and run cmake:

$ cmake .
-- Configuring done
-- Generating done
-- Build files have been written to: /home/khong/OpenCV/workspace/Tutorials
$ make
Scanning dependencies of target Tutorials
[100%] Building CXX object CMakeFiles/Tutorials.dir/t.cpp.o
Linking CXX executable Tutorials
[100%] Built target Tutorials

If we run the code:

$ ./Tutorials
img =
 [126,   0, 255, 126,   0, 255;
 126,   0, 255, 126,   0, 255]

If we modify the row from 2 to 5:

Mat img(2,2, CV_8UC3, Scalar(126,0,255));
==>
Mat img(5,2, CV_8UC3, Scalar(126,0,255));

We get:

img =
 [126,   0, 255, 126,   0, 255;
 126,   0, 255, 126,   0, 255;
 126,   0, 255, 126,   0, 255;
 126,   0, 255, 126,   0, 255;
 126,   0, 255, 126,   0, 255]

Here is the convention for the data type used in CV_8UC3:

CV_[The number of bits per item][Signed or Unsigned][Type Prefix]C[The channel number]

So, here is the meaning of the CV_8UC3:
we want to use unsigned char types('U') that are 8 bit long and each pixel has 3 of these to form the 3 channels. The Scalar is four element short vector.