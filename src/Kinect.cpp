#include "kinect.h"
#include <iostream>

Kinect::Kinect() {
	retVal = XN_STATUS_OK;

	// init openni context
	retVal = context.Init();
	if(retVal != XN_STATUS_OK) {
		std::cout << "failed to initialize context" << std::endl;
	}

	// create depth generator
	retVal = depthGen.Create(context);
	if(retVal != XN_STATUS_OK) {
		std::cout << "failed to create depth generator" << std::endl;
	}

	// mirror image
	retVal = context.SetGlobalMirror(!context.GetGlobalMirror());
	if(retVal != XN_STATUS_OK) {
		std::cout << "failed to set global mirror" << std::endl;
	}

	// start generating data
	retVal = context.StartGeneratingAll();
	if(retVal != XN_STATUS_OK) {
		std::cout << "failed to start generating data" << std::endl;
	}

	if(retVal == XN_STATUS_OK) {
		std::cout << "kinect initialized" << std::endl;
	}

	depthPixels = new unsigned char[XN_VGA_X_RES * XN_VGA_Y_RES];
}

Kinect::~Kinect() {
	context.Release();

	delete depthPixels;
	depthPixels = NULL;
}

unsigned char* Kinect::getDepthPixels(int nearThreshold, int farThreshold) {
	retVal = context.WaitOneUpdateAll(depthGen);
	if(retVal !=  XN_STATUS_OK) {
		std::cout << "failed to update data" << std::endl;
	}
	else {
		const XnDepthPixel* depthMap = depthGen.GetDepthMap();
	
		int numPixels = XN_VGA_X_RES * XN_VGA_Y_RES;
		for(int i = 0; i < numPixels; i++, depthMap++) {
			if(*depthMap < farThreshold && *depthMap > nearThreshold) {
				depthPixels[i] = 255;
			} else {
				depthPixels[i] = 0;
			}
		}
		return depthPixels;
	}
}

int Kinect::getWidth() {
	return XN_VGA_X_RES;
}

int Kinect::getHeight() {
	return XN_VGA_Y_RES;
}

int Kinect::getMaxDepth() {
	return depthGen.GetDeviceMaxDepth();
}
