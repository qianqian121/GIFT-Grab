# VideoTargetFactory
FILE(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/test_file_imshow.py
#        ${CMAKE_CURRENT_SOURCE_DIR}/virtual.py
        ${CMAKE_CURRENT_SOURCE_DIR}/test_cv_video_target.py
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
        )

SET(OPENCV_VISULIZATION_TEST test_opencv_visulization)
ADD_EXECUTABLE(
        ${OPENCV_VISULIZATION_TEST}
        test_opencv_visulization.cpp
)
TARGET_LINK_LIBRARIES(
        ${OPENCV_VISULIZATION_TEST}
        ${LIBS} ${NAME}
)
