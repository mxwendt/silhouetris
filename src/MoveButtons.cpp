#include "MoveButtons.h"

///////////////////////////////////////////////////////////////
MoveButtons::MoveButtons() {
	moveLeft = false;
	moveRight = false;

	sensitivity = 20;
}

MoveButtons::~MoveButtons() {
}

///////////////////////////////////////////////////////////////
void MoveButtons::update(vector<ofImage*> aImages) {
	unsigned char tempImage[70 * 480];
	setMoveBlock(aImages.at(0)->getPixels(0, 0, 70, 480, tempImage), LEFT);
	setMoveBlock(aImages.at(1)->getPixels(0, 0, 70, 480, tempImage), RIGHT);
}

void MoveButtons::drawMoveButtonLeft(int aX, int aY) {
	ofEnableAlphaBlending();
	ofSetColor(255, 0, 0, 80);
	ofRect(aX - 70, aY, 70, 480);
	ofDisableAlphaBlending();
}

void MoveButtons::drawMoveButtonRight(int aX, int aY) {
	ofEnableAlphaBlending();
	ofSetColor(255, 0, 0, 80);
	ofRect(aX + 360, aY, 70, 480);
	ofDisableAlphaBlending();
}

bool MoveButtons::isMoveLeft() {
	return moveLeft;
}

bool MoveButtons::isMoveRight() {
	return moveRight;
}

void MoveButtons::changeSensitivity(int aValue) {
	sensitivity += aValue;
	if(sensitivity < 0) {
		sensitivity = 0;
	}
	if(sensitivity > 70 * 480) {
		sensitivity = 70 * 480;
	}
}

///////////////////////////////////////////////////////////////
void MoveButtons::setMoveBlock(unsigned char* aPixels, int aDir) {
	int counter = 0;
	for(int i = 0; i < 70 * 480; i++) {	
		if (aPixels[i] != 255) {
			counter++;
		}
	}
	if(counter > sensitivity) {
		if(aDir == LEFT) {
			moveLeft = true;
		}
		if(aDir == RIGHT) {
			moveRight = true;
		}
		return;
	} 
	else {	
		if(aDir == LEFT) {
			moveLeft = false;
		}
		if(aDir == RIGHT) {
			moveRight = false;
		}
	}
}