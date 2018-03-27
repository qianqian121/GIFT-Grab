#include "pixelinksdk_video_source.h"
#include <iostream>

namespace gg
{

VideoSourcePixelinkSDK::VideoSourcePixelinkSDK(
    const std::string serial_num, PXL_PIXEL_FORMATS colour_space)
    : IVideoSource()
    , _camera(std::make_unique<PxLCamera>(std::stoi(serial_num)))
    , _flags(0)
    , _buffer(nullptr)
    , _image_size(0)
    , _daemon(nullptr)
{

    if (colour_space != YUV422)
    {
        // TODO - exception GiftGrab#42
        std::cerr << "Colour space " << colour_space << " not supported" << std::endl;
        return;
    }
    else if (colour_space == YUV422)
        _colour = UYVY;

    _flags |= colour_space;

    VideoFrame frame(_colour);
    /* TODO - e.g. PixelinkSDK_MAX_RES_X and
     * PixelinkSDK_MAX_RES_Y after
     * PixelinkSDK#6
     */
    PXL_RETURN_CODE rc;
    rc = _camera->getRoiValue(&_roi);
    if (!API_SUCCESS(rc)) {
        std::cerr << "error!";
    }
    _image_size = _camera->getImageSize();
    _full.m_width = 1920;
    _full.m_height = 1080;
    get_full_frame();
    // TODO - exception GiftGrab#42
    if (not get_frame(frame)) return;

    _daemon = new gg::BroadcastDaemon(this);
    _daemon->start(get_frame_rate());
}

VideoSourcePixelinkSDK::~VideoSourcePixelinkSDK()
{
    delete _daemon;
}

bool VideoSourcePixelinkSDK::get_frame_dimensions(int & width, int & height)
{
    width = _roi.m_width;
    height = _roi.m_height;
    return true;
}

bool VideoSourcePixelinkSDK::get_frame(VideoFrame & frame)
{
    if (frame.colour() != _colour)
        // TODO - exception GiftGrab#42
        return false;

//    _buffer = FrmGrab_Frame(_frame_grabber, _flags, &_roi);
    if (_buffer)
    {
        frame.init_from_specs(
                    static_cast<unsigned char*>(_buffer),
                    _image_size,
                    /* TODO #54 specified _roi not always
                     * respected by FrmGrab_Frame, hence
                     * constructing with _buffer->crop
                     * instead of _roi to avoid alignment
                     * problems when saving to video files
                     */
                    _roi.m_width, _roi.m_height
                    );
        return true;
    }
    else
        return false;
}

double VideoSourcePixelinkSDK::get_frame_rate()
{


    // TODO - exception GiftGrab#42
    return 0.0;
}

void VideoSourcePixelinkSDK::set_sub_frame(int x, int y, int width, int height)
{
//    if (x >= _full.x and x + width <= _full.x + _full.width and
//        y >= _full.y and y + height <= _full.y + _full.height)
//    {
//        _roi.x = x;
//        _roi.y = y;
//        _roi.width = width;
//        _roi.height = height;
//    }
    // TODO - exception GiftGrab#42
//    else
//        throw VideoSourceError("ROI " + std::to_string(x) + ", " +
//                               std::to_string(y) + ", " +
//                               std::to_string(width) + ", " +
//                               std::to_string(height) + ", " +
//                               "not within full frame");
}

void VideoSourcePixelinkSDK::get_full_frame()
{
//    _roi.x = _full.x;
//    _roi.y = _full.y;
    _roi.m_width = _full.m_width;
    _roi.m_height = _full.m_height;
}

} // namespace gg
