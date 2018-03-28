# VideoTargetFactory
SET(OPENCV_VISULIZATION_TEST test_opencv_visulization)
ADD_EXECUTABLE(
        ${OPENCV_VISULIZATION_TEST}
        test_opencv_visulization.cpp
)
TARGET_LINK_LIBRARIES(
        ${VIDEO_TARGET_FACTORY_TEST}
        ${LIBS} ${NAME}
)
