#include "Piece.h"

///////////////////////////////////////////////////////////////
Piece::Piece() {
	// clear blocks
	for(int i = 0; i < PIECE_COLUMNS; i++) {
		for(int j = 0; j < PIECE_ROWS; j++) {
			blocks[i][j] = false;
		}
	}

	moveLeft = false;
	moveRight = false;

	sensitivity = 10;
}

Piece::~Piece() {}

///////////////////////////////////////////////////////////////
void Piece::update(ofImage* aDepthImage) {
	unsigned char tempActiveBlock[120 * 120];
	setActiveBlock(aDepthImage->getPixels( 70,   0, 120, 120, tempActiveBlock), 0, 0);
	setActiveBlock(aDepthImage->getPixels(190,   0, 120, 120, tempActiveBlock), 0, 1);
	setActiveBlock(aDepthImage->getPixels(310,   0, 120, 120, tempActiveBlock), 0, 2);
	setActiveBlock(aDepthImage->getPixels( 70, 120, 120, 120, tempActiveBlock), 1, 0);
	setActiveBlock(aDepthImage->getPixels(190, 120, 120, 120, tempActiveBlock), 1, 1);
	setActiveBlock(aDepthImage->getPixels(310, 120, 120, 120, tempActiveBlock), 1, 2);
	setActiveBlock(aDepthImage->getPixels( 70, 240, 120, 120, tempActiveBlock), 2, 0);
	setActiveBlock(aDepthImage->getPixels(190, 240, 120, 120, tempActiveBlock), 2, 1);
	setActiveBlock(aDepthImage->getPixels(310, 240, 120, 120, tempActiveBlock), 2, 2);
	setActiveBlock(aDepthImage->getPixels( 70, 360, 120, 120, tempActiveBlock), 3, 0);
	setActiveBlock(aDepthImage->getPixels(190, 360, 120, 120, tempActiveBlock), 3, 1);
	setActiveBlock(aDepthImage->getPixels(310, 360, 120, 120, tempActiveBlock), 3, 2);

	unsigned char tempMoveBlock[70 * 480];
	setMoveBlock(aDepthImage->getPixels(0, 0, 70, 480, tempMoveBlock), LEFT);
	setMoveBlock(aDepthImage->getPixels(430, 0, 70, 480, tempMoveBlock), RIGHT);
}

void Piece::drawOverlay(int aX, int aY, int aWidth, int aHeight) {
	ofEnableAlphaBlending();
	ofSetColor(186, 205, 54, 80);
	for(int i = 0; i < PIECE_COLUMNS; i++) {
		for(int j = 0; j < PIECE_ROWS; j++) {
			if(blocks[i][j]) {
				ofRect((aWidth / PIECE_COLUMNS) * i + aX, (aHeight / PIECE_ROWS) * j + aY, aWidth / PIECE_COLUMNS, aHeight / PIECE_ROWS);
			}
		}
	}
	ofDisableAlphaBlending();
}

void Piece::drawMoveButtons(int aX, int aY) {
	ofEnableAlphaBlending();
	ofSetColor(255, 0, 0, 80);
	if(moveLeft) {
		ofRect(aX - 70, aY, 70, 480);
	} 
	else if(moveRight) {
		ofRect(aX + 360, aY, 70, 480);
	}
	ofDisableAlphaBlending();
}

void Piece::drawPiece(int aX, int aY, int aWidth, int aHeight) {
	ofSetColor(186, 205, 54);
	for(int i = 0; i < PIECE_COLUMNS; i++) {
		for(int j = 0; j < PIECE_ROWS; j++) {
			if(blocks[i][j]) {
				ofRect((aWidth / PIECE_COLUMNS) * i + aX, (aHeight / PIECE_ROWS) * j + aY, aWidth / PIECE_COLUMNS, aHeight / PIECE_ROWS);
			}
		}
	}
}

bool Piece::isActiveBlock(int aCol, int aRow) {
	return blocks[aCol][aRow];
}

bool Piece::isMoveLeft() {
	return moveLeft;
}

bool Piece::isMoveRight() {
	return moveRight;
}

bool Piece::isEmpty() {
	// check if somebody is in the tracking area
	if(blocks[0][0] || blocks[0][1] ||
	   blocks[0][2] || blocks[0][3] ||
	   blocks[1][0] || blocks[1][1] ||
	   blocks[1][2] || blocks[1][3] ||
	   blocks[2][0] || blocks[2][1] ||
	   blocks[2][2] || blocks[2][3]) {
		return false;
	}
	else {
		return true;
	}
}

bool Piece::isCross() {
	// check for cross to start a game
	if(blocks[1][0] && blocks[0][1] &&
	   blocks[1][1] && blocks[2][1] && 
	   blocks[1][2] && blocks[1][3] &&
	   !blocks[0][0] && !blocks[2][0] &&
	   !blocks[0][2] && !blocks[2][2] &&
	   !blocks[0][3] && !blocks[2][3]) {
		return true;
	}
	else {
		return false;
	}
}

void Piece::reset() {
	// clear blocks
	for(int i = 0; i < PIECE_COLUMNS; i++) {
		for(int j = 0; j < PIECE_ROWS; j++) {
			blocks[i][j] = false;
		}
	}
}

void Piece::changeSensitivity(int aValue) {
	sensitivity += aValue;
	if(sensitivity < 0) {
		sensitivity = 0;
	}
	if(sensitivity > PIECE_WIDTH * PIECE_HEIGHT) {
		sensitivity = PIECE_WIDTH * PIECE_HEIGHT
	}
}

///////////////////////////////////////////////////////////////
void Piece::setActiveBlock(unsigned char* aPixels, int aCol, int aRow) {
	int counter = 0;
	for(int i = 0; i < 120 * 120; i++) {
		if(aPixels[i] != 255) {
			counter++;
		}
	}
	if(counter > sensitivity) {
		blocks[aRow][aCol] = true; 
		return;
	} 
	else {
		blocks[aRow][aCol] = false;
	}
}

void Piece::setMoveBlock(unsigned char* aPixels, int aDir) {
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
