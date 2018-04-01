//
// Created by dev on 3/28/18.
//
#include "videoframe.h"
#include "videosourcefactory.h"
#include "videotargetfactory.h"

#include <chrono>
#include <thread>
#include <opencv_video_source.h>
#include <pixelinksdk_video_source.h>

int main(int argc, char* argv[]) {
    using namespace std::chrono_literals;

    //
    // Step 2
    //      Determine how many cameras are connected, and then get the serial
    uint32_t numCameras;
    PxLGetNumberCameras (NULL, &numCameras);
    std::cout << numCameras <<std::endl;

    IVideoSource * source = nullptr;

    source = new gg::VideoSourcePixelinkSDK("0", BAYER8);    // 2B36A811    // 725002257

    gg::VideoTargetFactory & factory_target = gg::VideoTargetFactory::get_instance();
    gg::IVideoTarget * target = nullptr;
//    gg::Codec codec = gg::Codec::Xvid;    // opencv
//    target = factory_target.create_file_writer(codec, "opencv_output.avi", 30.0);

    gg::Codec codec = gg::Codec::HEVC;
    target = factory_target.create_file_writer(codec, "ffmpeg.mp4", 30.0);

    source->attach(*target);
    std::this_thread::sleep_for(20s);
    source->detach(*target);
    delete target;
    return 0;
}
