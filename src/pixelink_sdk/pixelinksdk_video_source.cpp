#include "pixelinksdk_video_source.h"
#include <iostream>
#include <opencv/cv.hpp>

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

    if (colour_space != BAYER8)
    {
        // TODO - exception GiftGrab#42
        std::cerr << "Colour space " << colour_space << " not supported" << std::endl;
        return;
    }
    else if (colour_space == BAYER8)
        _colour = BGRA;
//        _colour = UYVY;

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

    float currentValue;
    _camera->getValue(FEATURE_PIXEL_FORMAT, &currentValue);
    std::cout << "Current pixel format: " << currentValue << std::endl; // PIXEL_FORMAT_BAYER8_RGGB      7

//    rc = _camera->setValue(FEATURE_PIXEL_FORMAT, PxLPixelFormat_toApi(colour_space));
//    if (!API_SUCCESS(rc)) {
//        std::cerr << "error!";
//    }

    _image_size = _camera->getImageSize();
    _buffer = std::make_unique<uint8_t []>(_image_size);
    // FIXME easy 20180331 - x265 ffmpeg only works at 1920x1080. Need to manually set ROI first.

//    _full.m_width = 1920;
//    _full.m_height = 1080;
//    get_full_frame();
    // TODO - exception GiftGrab#42
    rc = _camera->play();
    if (!get_frame(frame)) return;

    _daemon = new gg::BroadcastDaemon(this);
    _daemon->start(get_frame_rate());
}

VideoSourcePixelinkSDK::~VideoSourcePixelinkSDK()
{
    if (_camera->streaming())
        _camera->stop();
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
    PXL_RETURN_CODE rc;

    if (frame.colour() != _colour)
        // TODO - exception GiftGrab#42
        return false;

    rc = _camera->getNextFrame(_image_size, _buffer.get());
    cv::Mat cv_frame_bayerbg(_roi.m_height, _roi.m_width,
                          CV_8UC1,
                          const_cast<unsigned char *>(_buffer.get()));
    cv::Mat cv_frame_bgra(_roi.m_height, _roi.m_width, CV_8UC4);
    cv::cvtColor(cv_frame_bayerbg, cv_frame_bgra, CV_BayerRG2BGRA);

//    std::vector<uchar> array;
////    if (cv_frame_bgra.isContinuous()) {
////        array.assign(cv_frame_bgra.datastart, cv_frame_bgra.dataend);
////    } else {
//        for (int i = 0; i < cv_frame_bgra.rows; ++i) {
//            array.insert(array.end(), cv_frame_bgra.ptr<uchar>(i), cv_frame_bgra.ptr<uchar>(i)+cv_frame_bgra.cols);
//        }
////    }
//    unsigned return_buff[(cv_frame_bgra.total() * cv_frame_bgra.channels())];
//    cv_frame_bgra.(0, 0, return_buff);

//    std::vector<cv::Vec<uchar,1>> pixels[_roi.m_height * _roi.m_width*4];
    std::vector<cv::Vec4b> pixels(_roi.m_height * _roi.m_width);
    std::vector<uchar> array(_roi.m_height * _roi.m_width * 4);

//    std::vector<cv::Vec4b> pixels;
//    std::vector<uchar> pixels(_roi.m_height * _roi.m_width*4);
//    cv::Mat m(_roi.m_height, _roi.m_width, CV_8UC4, &pixels[0]);
//    cv::MatIterator_<cv::Vec<uchar,1>> it, end;
    cv::MatIterator_<cv::Vec4b> it, end;
    size_t i = 0;
//    for(it = cv_frame_bgra.begin<cv::Vec<uchar,1>>(), end = cv_frame_bgra.end<cv::Vec<uchar,1>>(); it != end; ++it, ++i)
    for(it = cv_frame_bgra.begin<cv::Vec4b>(), end = cv_frame_bgra.end<cv::Vec4b>(); it != end; ++it)
    {
//        pixels[i] = (*it);
        array[i++] = (*it)[0];
        array[i++] = (*it)[1];
        array[i++] = (*it)[2];
        array[i++] = (*it)[3];
    }

////    cv_frame_bgra.copyTo(m);
////    std::vector<uchar> array(_roi.m_height * _roi.m_width * 4);
////    for (int64_t i = 0; i < pixels->size(); i++) {
////        array[i] = reinterpret_cast<unsigned char *>(pixels[i][0].val)[0];
////    }
//    cv::Mat cv_frame_bgra_test(_roi.m_height, _roi.m_width,
//                          CV_8UC4,
//                          (&array[0]));
////    cv::Mat cv_frame_bgra_test(_roi.m_height, _roi.m_width,
////                               CV_8UC4,
////                               const_cast<unsigned char *>(&pixels[0]));
//    cv::Mat _buffer_bgr;//  = cv::Mat::zeros(frame.rows(), frame.cols(),CV_8UC3);
//    cv::cvtColor(cv_frame_bgra_test, _buffer_bgr, CV_BGRA2BGR);
////        easy 20180329 debug imshow
//    cv::imshow("cv imshow", _buffer_bgr);
//    cv::waitKey(30);
//
////    cv::imshow("video", cv_frame_bgra);
////    cv::waitKey(30);
    if (API_SUCCESS(rc))
    {
        // TODO easy 20180331 - check wether managed frame or not, to make sure zero copy
        frame.init_from_specs(
//                static_cast<unsigned char *>(_buffer.get()),
//                cv_frame_bayerbg.data,
//                                cv_frame_bgra.data,
                                static_cast<unsigned char *>(&array[0]),
                                _roi.m_height * _roi.m_width*4,
//                cv_frame_bgra.data,
//                    _image_size * 3,
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

//    bool VideoSourcePixelinkSDK::get_frame(VideoFrame & frame)
//    {
//        PXL_RETURN_CODE rc;
//
//        if (frame.colour() != _colour)
//            // TODO - exception GiftGrab#42
//            return false;
//
//        rc = _camera->getNextFrame(_image_size, _buffer.get());
//        cv::Mat cv_frame_bayerbg(_roi.m_height, _roi.m_width,
//                                 CV_8UC1,
//                                 const_cast<unsigned char *>(_buffer.get()));
//        cv::Mat cv_frame_bgra;
//        cv::cvtColor(cv_frame_bayerbg, cv_frame_bgra, CV_BayerRG2BGRA);
//        if (API_SUCCESS(rc))
//        {
//            // TODO easy 20180331 - check wether managed frame or not, to make sure zero copy
//            frame.init_from_specs(
//                    cv_frame_bgra.data,
//                    cv_frame_bgra.step[0] /3 * 4 * cv_frame_bgra.rows,
//                    /* TODO #54 specified _roi not always
//                     * respected by FrmGrab_Frame, hence
//                     * constructing with _buffer->crop
//                     * instead of _roi to avoid alignment
//                     * problems when saving to video files
//                     */
//                    _roi.m_width, _roi.m_height
//            );
//            return true;
//        }
//        else
//            return false;
//    }

double VideoSourcePixelinkSDK::get_frame_rate()
{


    // TODO - exception GiftGrab#42
    return 3.0;
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
