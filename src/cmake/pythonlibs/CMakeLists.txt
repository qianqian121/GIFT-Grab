CMAKE_MINIMUM_REQUIRED(VERSION 3.2.0)

FIND_PACKAGE(PythonLibs 3.5 REQUIRED)
SET(PYTHON_INCLUDE_DIRS ${PYTHON_INCLUDE_DIRS}
    CACHE INTERNAL "PythonLibs include dirs"
)
SET(PYTHON_LIBRARIES ${PYTHON_LIBRARIES}
    CACHE INTERNAL "PythonLibs libraries"
)
