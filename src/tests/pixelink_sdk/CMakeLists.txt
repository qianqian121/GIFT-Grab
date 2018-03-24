FILE(COPY
    test_unit.py
    test_observer.py
    conftest.py
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

# VideoSourceFactory
SET(VIDEO_SOURCE_FACTORY_TEST test_video_source_factory_pixelink_sdk)
ADD_EXECUTABLE(
    ${VIDEO_SOURCE_FACTORY_TEST}
    ${CMAKE_SOURCE_DIR}/tests/pixelink_sdk/test_video_source_factory.cpp
)
TARGET_LINK_LIBRARIES(
    ${VIDEO_SOURCE_FACTORY_TEST}
    ${LIBS} ${NAME}
)
SET(COLOUR_SPACE UYVY)

SET(NAME_TEST Test_Pixelink_SDK_VideoSourceFactory_${COLOUR_SPACE})
ADD_TEST(NAME ${NAME_TEST} COMMAND ${VIDEO_SOURCE_FACTORY_TEST})
LIST(APPEND TESTS_LIST ${NAME_TEST})

# Pixelink SDK on its own
SET(NAME_TEST Test_Pixelink_SDK_${COLOUR_SPACE})
ADD_TEST(NAME ${NAME_TEST}
    COMMAND py.test --colour-space=${COLOUR_SPACE} test_unit.py
)
LIST(APPEND TESTS_LIST ${NAME_TEST})

# Pixelink SDK using the observer design pattern
SET(NAME_TEST Test_Pixelink_SDK_ObserverPattern_${COLOUR_SPACE})
SET(FRAME_RATE 25)
ADD_TEST(NAME ${NAME_TEST}
    COMMAND py.test --colour-space=${COLOUR_SPACE} --frame-rate=${FRAME_RATE} --observers=3 test_observer.py
)
LIST(APPEND TESTS_LIST ${NAME_TEST})

# to avoid copying stuff around
SET_TESTS_PROPERTIES(${TESTS_LIST}
    PROPERTIES ENVIRONMENT "PYTHONPATH=${PYTHONPATH}"
)
