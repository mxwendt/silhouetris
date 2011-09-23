#ifndef _KINECT
#define _KINECT

#include "XnCppWrapper.h"

class Kinect {
public:
	Kinect();
	~Kinect();

	unsigned char* getDepthPixels(int nearThreshold, int farThreshold);
	int getWidth();
	int getHeight();
	int getMaxDepth();

	XnStatus retVal;
	xn::Context context;
	xn::DepthGenerator depthGen;
	unsigned char* depthPixels;
};

#endif
