# VideoTargetFactory
SET(PIXELINK_SDK_TEST test_pixelink_sdk)
ADD_EXECUTABLE(
        ${PIXELINK_SDK_TEST}
        test_pixelink_preview.cpp
)
TARGET_LINK_LIBRARIES(
        ${PIXELINK_SDK_TEST}
        ${LIBS} ${NAME}
)
