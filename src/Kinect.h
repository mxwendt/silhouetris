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
	void separateImage();
	void drawDepthImage(int aX, int aY, int aW, int aH);
	void drawBlockImages();
	void drawButtonImages();

	void changeThreshold(int aNear, int aFar);

	vector<ofImage*> getImages();

private:
	///////////////////////////////////////////////////////////////
	XnStatus retVal;
	xn::Context context;
	xn::DepthGenerator depthGen;

	unsigned char* depthPixels;
	ofImage* depthMask;
	ofImage* depthButtonLeft;
	ofImage* depthButtonRight;
	ofImage* depthBlock00;
	ofImage* depthBlock01;
	ofImage* depthBlock02;
	ofImage* depthBlock03;
	ofImage* depthBlock10;
	ofImage* depthBlock11;
	ofImage* depthBlock12;
	ofImage* depthBlock13;
	ofImage* depthBlock20;
	ofImage* depthBlock21;
	ofImage* depthBlock22;
	ofImage* depthBlock23;

	vector<ofImage*> images;

	int nearThreshold;
	int farThreshold;
};

#endif
