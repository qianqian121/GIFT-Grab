CMAKE_MINIMUM_REQUIRED(VERSION 3.2.0)

#TODO easy 20180324 set correct pixelink source dir after code refactor
SET(Pixelink_SDK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../pixelink_sdk)
MESSAGE(WARNING ${Pixelink_SDK_DIR})

if(NOT Pixelink_SDK_DIR)
    MESSAGE(FATAL_ERROR
        "Pixelink_SDK_DIR does not seem to be set in your cmake. This is needed to find Pixelink Desktop Video SDK components.")
endif(NOT DEFINED ENV{Pixelink_SDK_DIR})

#TODO easy 20180324 move pixelink to docker /opt and update find_library
#FIND_LIBRARY(DeckLinkAPI_LIB
#    NAMES DeckLinkAPI
#    PATHS /usr/lib
#)
#if(NOT DeckLinkAPI_LIB)
#    MESSAGE(FATAL_ERROR
#        "Blackmagic DeckLink drivers do not seem to be installed on your system. They are needed for capturing video using a Blackmagic card.")
#endif(NOT DeckLinkAPI_LIB)

SET(Pixelink_SDK_INCLUDE_DIRS
    $ENV{Pixelink_SDK_DIR}/include
    CACHE INTERNAL "Blackmagic Desktop Video SDK include dirs"
)

SET(Pixelink_SDK_LIBS
    $ENV{Pixelink_SDK_DIR}/lib
    CACHE INTERNAL "Blackmagic Desktop Video SDK libs to link against"
)
