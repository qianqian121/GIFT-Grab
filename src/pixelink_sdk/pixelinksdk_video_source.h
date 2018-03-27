#pragma once

#include "src/pixelFormat.h"
#include "src/camera.h"
#include "ivideosource.h"
#include "macros.h"
#include "broadcastdaemon.h"

namespace gg
{

class VideoSourcePixelinkSDK : public IVideoSource
{
protected:
    //!
    //! \brief
    //!
    std::unique_ptr<PxLCamera> _camera;

    //!
    //! \brief Currently only colour space
    //!
    int _flags;

    //!
    //! \brief Full frame dimensions
    //!
    PXL_ROI _full;

    //!
    //! \brief Region of interest, i.e. sub-frame
    //! \sa _full
    //!
    PXL_ROI _roi;

    //!
    //! \brief Buffer for acquiring frame data
    //! \sa _frame_grabber
    //!
    uint8_t * _buffer;

    uint32_t _image_size;

    //!
    //! \brief
    //!
    gg::BroadcastDaemon * _daemon;

public:
    //!
    //! \brief Connects to specified port of an Pixelink
    //! frame grabber
    //! \param device_id defines port of frame grabber,
    //! as \c \#define'd in Pixelink device properties
    //! header
    //! \param colour_space \c V2U_GRABFRAME_FORMAT_I420
    //! or \c V2U_GRABFRAME_FORMAT_BGR24
    //! \throw VideoSourceError if connection attempt
    //! fails, with a detailed error message
    //!
    VideoSourcePixelinkSDK(const std::string serial_num,
                           PXL_PIXEL_FORMATS colour_space);

    //!
    //! \brief Release all allocated resources
    //!
    virtual ~VideoSourcePixelinkSDK();

public:
    bool get_frame_dimensions(int & width, int & height);

    bool get_frame(VideoFrame & frame);

    double get_frame_rate();

    void set_sub_frame(int x, int y, int width, int height);

    void get_full_frame();

protected:
    DISALLOW_COPY_AND_ASSIGNMENT(VideoSourcePixelinkSDK);
};

}
