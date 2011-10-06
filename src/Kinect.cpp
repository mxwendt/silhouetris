#include "Kinect.h"

///////////////////////////////////////////////////////////////
Kinect::Kinect(int aNearThreshold, int aFarThreshold) {
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

	// set trackable range
	nearThreshold = aNearThreshold;
	farThreshold = aFarThreshold;

	// create images to work w/ depth stream data
	depthPixels = new unsigned char[XN_VGA_X_RES * XN_VGA_Y_RES];
	depthMask = new ofImage();

	// create image for move left button
	depthButtonLeft = new ofImage();

	// create image for move right button
	depthButtonRight = new ofImage();

	//create images for the 12 different blocks
	depthBlock00 = new ofImage();
	depthBlock01 = new ofImage();
	depthBlock02 = new ofImage();
	depthBlock03 = new ofImage();
	depthBlock10 = new ofImage();
	depthBlock11 = new ofImage();
	depthBlock12 = new ofImage();
	depthBlock13 = new ofImage();
	depthBlock20 = new ofImage();
	depthBlock21 = new ofImage();
	depthBlock22 = new ofImage();
	depthBlock23 = new ofImage();

	// save images
	images.push_back(depthButtonLeft);
	images.push_back(depthButtonRight);
	images.push_back(depthBlock00);
	images.push_back(depthBlock01);
	images.push_back(depthBlock02);
	images.push_back(depthBlock03);
	images.push_back(depthBlock10);
	images.push_back(depthBlock11);
	images.push_back(depthBlock12);
	images.push_back(depthBlock13);
	images.push_back(depthBlock20);
	images.push_back(depthBlock21);
	images.push_back(depthBlock22);
	images.push_back(depthBlock23);
}

Kinect::~Kinect() {
	context.Release();

	// clean up
	delete depthPixels;
	depthPixels = NULL;

	delete depthMask;
	depthMask = NULL;

	delete depthButtonLeft;
	depthButtonLeft = NULL;

	delete depthButtonRight;
	depthButtonRight = NULL;

	delete depthBlock00;
	depthBlock00 = NULL;

	delete depthBlock01;
	depthBlock01 = NULL;

	delete depthBlock02;
	depthBlock02 = NULL;

	delete depthBlock03;
	depthBlock03 = NULL;

	delete depthBlock10;
	depthBlock10 = NULL;

	delete depthBlock11;
	depthBlock11 = NULL;

	delete depthBlock12;
	depthBlock12 = NULL;

	delete depthBlock13;
	depthBlock13 = NULL;

	delete depthBlock20;
	depthBlock20 = NULL;

	delete depthBlock21;
	depthBlock21 = NULL;

	delete depthBlock22;
	depthBlock22 = NULL;

	delete depthBlock23;
	depthBlock23 = NULL;
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
	}
}

void Kinect::separateImage() {
	// seperate the move buttons
	unsigned char tempImage1[70 * 480];
	depthButtonLeft->setFromPixels(depthMask->getPixels(70, 0, 70, 480, tempImage1), 70, 480, OF_IMAGE_GRAYSCALE);
	depthButtonRight->setFromPixels(depthMask->getPixels(500, 0, 70, 480, tempImage1), 70, 480, OF_IMAGE_GRAYSCALE);
	
	// seperate the 12 different blocks
	unsigned char tempImage2[120 * 120];
	depthBlock00->setFromPixels(depthMask->getPixels(140,   0, 120, 120, tempImage2), 120, 120, OF_IMAGE_GRAYSCALE);
	depthBlock01->setFromPixels(depthMask->getPixels(140, 120, 120, 120, tempImage2), 120, 120, OF_IMAGE_GRAYSCALE);
	depthBlock02->setFromPixels(depthMask->getPixels(140, 240, 120, 120, tempImage2), 120, 120, OF_IMAGE_GRAYSCALE);
	depthBlock03->setFromPixels(depthMask->getPixels(140, 360, 120, 120, tempImage2), 120, 120, OF_IMAGE_GRAYSCALE);
	depthBlock10->setFromPixels(depthMask->getPixels(260,   0, 120, 120, tempImage2), 120, 120, OF_IMAGE_GRAYSCALE);
	depthBlock11->setFromPixels(depthMask->getPixels(260, 120, 120, 120, tempImage2), 120, 120, OF_IMAGE_GRAYSCALE);
	depthBlock12->setFromPixels(depthMask->getPixels(260, 240, 120, 120, tempImage2), 120, 120, OF_IMAGE_GRAYSCALE);
	depthBlock13->setFromPixels(depthMask->getPixels(260, 360, 120, 120, tempImage2), 120, 120, OF_IMAGE_GRAYSCALE);
	depthBlock20->setFromPixels(depthMask->getPixels(380,   0, 120, 120, tempImage2), 120, 120, OF_IMAGE_GRAYSCALE);
	depthBlock21->setFromPixels(depthMask->getPixels(380, 120, 120, 120, tempImage2), 120, 120, OF_IMAGE_GRAYSCALE);
	depthBlock22->setFromPixels(depthMask->getPixels(380, 240, 120, 120, tempImage2), 120, 120, OF_IMAGE_GRAYSCALE);
	depthBlock23->setFromPixels(depthMask->getPixels(380, 360, 120, 120, tempImage2), 120, 120, OF_IMAGE_GRAYSCALE);
}

void Kinect::drawBlockImages() {
	depthBlock00->draw(569, 24);
	depthBlock01->draw(569, 144);
	depthBlock02->draw(569, 264);
	depthBlock03->draw(569, 384);
	depthBlock10->draw(689, 24);
	depthBlock11->draw(689, 144);
	depthBlock12->draw(689, 264);
	depthBlock13->draw(689, 384);
	depthBlock20->draw(809, 24);
	depthBlock21->draw(809, 144);
	depthBlock22->draw(809, 264);
	depthBlock23->draw(809, 384);
}

void Kinect::drawButtonImages() {
	depthButtonLeft->draw(499, 24);
	depthButtonRight->draw(929, 24);
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

vector<ofImage*> Kinect::getImages() {
	return images;
}
