
CXX=g++
INCLUDES=-I$(PIXELINK_SDK_INC)
LIBPATH=-L$(PIXELINK_SDK_LIB) 
DEFINES=-DPIXELINK_LINUX
# This sample app works with both the full API (PxLApi), or the reduced
# functionality BareBonesAPI (PxLApiBB).  Choose the LIBS definition
# accordingly
#LIBS=-lPxLApiBB
LIBS=-lPxLApi -lJPEGDLL32
CFLAGS=-O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP $(DEFINES) $(INCLUDES)

SRCFILES=multiCameraPreview.cpp LinuxUtil.cpp
OBJFILES=$(SRCFILES:.cpp=.o)

all: multiCameraPreview

multiCameraPreview: $(OBJFILES) 
	rm -f $@
	$(CXX) $(LIBPATH) -o $@ $^ $(LIBS)

.cpp.o:
	$(CXX) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o
	rm -rf multiCameraPreview


