#include "videoframe_i420.h"
#include <cstring>

namespace gg
{

VideoFrame_I420::VideoFrame_I420(bool manage_data)
    : VideoFrame(manage_data)
{

}

VideoFrame_I420::VideoFrame_I420(unsigned char * data, const size_t length,
                                 const size_t cols, const size_t rows,
                                 bool manage_data)
    : VideoFrame(manage_data)
{
    init_from_pointer(data, length, cols, rows);
}

void VideoFrame_I420::operator =(const VideoFrame_I420 & rhs)
{
    _manage_data = true;
    init_from_pointer(rhs._data, rhs._data_length,
                      rhs._cols, rhs._rows);
}

void VideoFrame_I420::init_from_pointer(
    unsigned char * data, size_t length,
    size_t cols, size_t rows)
{
    // TODO - check length vs rows and cols?
    _data_length = length;
    _cols = cols;
    _rows = rows;
    if (_manage_data)
    {
        _data = new unsigned char[_data_length];
        memcpy(_data, data, _data_length);
    }
    else
        _data = data;
}

}
