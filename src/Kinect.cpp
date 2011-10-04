#include "Kinect.h"

///////////////////////////////////////////////////////////////
Kinect::Kinect(int aNearThreshold, int aFarThreshold) {
	nearThreshold = aNearThreshold;
	farThreshold = aFarThreshold;

	retVal = XN_STATUS_OK;

	// init openni context
	retVal = context.Init();
	if(retVal != XN_STATUS_OK) {
		std::cout << "ERROR: failed to initialize context" << std::endl;
	}

	// create depth generator
	retVal = depthGen.Create(context);
	if(retVal != XN_STATUS_OK) {
		std::cout << "ERROR: failed to create depth generator" << std::endl;
	}

	// mirror image
	retVal = context.SetGlobalMirror(!context.GetGlobalMirror());
	if(retVal != XN_STATUS_OK) {
		std::cout << "ERROR: failed to set global mirror" << std::endl;
	}

	// start generating data
	retVal = context.StartGeneratingAll();
	if(retVal != XN_STATUS_OK) {
		std::cout << "ERROR: failed to start generating data" << std::endl;
	}

	if(retVal == XN_STATUS_OK) {
		std::cout << "kinect initialized" << std::endl;
	}

	depthPixels = new unsigned char[XN_VGA_X_RES * XN_VGA_Y_RES];
	depthMask = new ofImage();
	depthImage = new ofImage();
}

Kinect::~Kinect() {
	context.Release();

	delete depthPixels;
	depthPixels = NULL;

	delete depthMask;
	depthMask = NULL;

	delete depthImage;
	depthImage = NULL;
}

///////////////////////////////////////////////////////////////
void Kinect::updateDepthImage() {
	retVal = context.WaitOneUpdateAll(depthGen);
	if(retVal !=  XN_STATUS_OK) {
		std::cout << "ERROR: failed to update data" << std::endl;
		// TODO: handle failure
	}
	else {
		const XnDepthPixel* depthMap = depthGen.GetDepthMap();
	
		int numPixels = XN_VGA_X_RES * XN_VGA_Y_RES;
		for(int i = 0; i < numPixels; i++, depthMap++) {
			if(*depthMap > nearThreshold && *depthMap < farThreshold) {
				depthPixels[i] = 0;
			} else {
				depthPixels[i] = 255;
			}
		}
		
		depthMask->setFromPixels(depthPixels, XN_VGA_X_RES, XN_VGA_Y_RES, OF_IMAGE_GRAYSCALE);
	
		unsigned char image[XN_VGA_X_RES * XN_VGA_Y_RES];
		depthImage->setFromPixels(depthMask->getPixels(70, 0, 500, 480, image), 500, 480, OF_IMAGE_GRAYSCALE);
	}
}

void Kinect::drawDepthImage(int aX, int aY, int aW, int aH) {
	depthImage->draw(aX, aY, aW, aH);
}

void Kinect::changeThreshold(int aNear, int aFar) {
	nearThreshold += aNear;
	if(nearThreshold > depthGen.GetDeviceMaxDepth()) {
		nearThreshold = depthGen.GetDeviceMaxDepth();
	}
	else if(nearThreshold < 0) {
		nearThreshold = 0;
	}

	farThreshold += aFar;
	if(farThreshold > depthGen.GetDeviceMaxDepth()) {
		farThreshold = depthGen.GetDeviceMaxDepth();
	}
	else if(farThreshold < 0) {
		farThreshold = 0;
	}
}

ofImage* Kinect::getDepthImage() {
	return depthImage;
}
