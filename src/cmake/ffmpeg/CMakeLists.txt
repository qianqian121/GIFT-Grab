CMAKE_MINIMUM_REQUIRED(VERSION 3.2.0)

# Augment module path to be able to find needed packages
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

FIND_PACKAGE(FFmpeg REQUIRED)
SET(FFmpeg_INCLUDE_DIRS ${FFmpeg_INCLUDE_DIRS}
    CACHE INTERNAL "FFmpeg include dirs"
)
SET(FFmpeg_LIBS ${FFmpeg_LIBS}
    CACHE INTERNAL "FFmpeg libs"
)
SET(FFmpeg_LIBRARY_DIRS ${FFmpeg_LIBRARY_DIRS}
    CACHE INTERNAL "FFmpeg library dirs"
)

message(WARNING ${FFmpeg_LIBRARY_DIRS})