#ifndef _KINECT
#define _KINECT

#include "XnCppWrapper.h"
#include "ofMain.h"

class Kinect {
public:
	///////////////////////////////////////////////////////////////
	Kinect(int aNearThreshold, int aFarThreshold);
	~Kinect();

	///////////////////////////////////////////////////////////////
	void updateDepthImage();
	void drawDepthImage(int aX, int aY, int aW, int aH);

	void changeThreshold(int aNear, int aFar);

	ofImage* getDepthImage();

private:
	///////////////////////////////////////////////////////////////
	XnStatus retVal;
	xn::Context context;
	xn::DepthGenerator depthGen;

	unsigned char* depthPixels;
	ofImage* depthMask;
	ofImage* depthImage;

	int nearThreshold;
	int farThreshold;
};

#endif
