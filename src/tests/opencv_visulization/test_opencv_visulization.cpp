//
// Created by dev on 3/28/18.
//
#include "videoframe.h"
#include "videosourcefactory.h"
#include "videotargetfactory.h"

#include <chrono>
#include <thread>

int main(int argc, char* argv[]) {
    using namespace std::chrono_literals;
    gg::ColourSpace colour = gg::BGRA;
    std::string filepath = "data/video_15frames_30fps.avi";
    gg::VideoSourceFactory & factory = gg::VideoSourceFactory::get_instance();

    IVideoSource * source = nullptr;

    source = factory.create_file_reader(filepath, colour);

    gg::VideoTargetFactory & factory_target = gg::VideoTargetFactory::get_instance();
    gg::IVideoTarget * target = nullptr;
    gg::Codec codec = gg::Codec::Xvid;
    target = factory_target.create_file_writer(codec, "opencv_output.avi", 30.0);

    source->attach(*target);
    std::this_thread::sleep_for(2s);
    source->detach(*target);
    delete target;
    return 0;
}
