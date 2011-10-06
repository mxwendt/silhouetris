#include "Piece.h"

///////////////////////////////////////////////////////////////
Piece::Piece() {
	// clear blocks
	for(int i = 0; i < PIECE_COLUMNS; i++) {
		for(int j = 0; j < PIECE_ROWS; j++) {
			blocks[i][j] = false;
		}
	}

	sensitivity = 10;
}

Piece::~Piece() {}

///////////////////////////////////////////////////////////////
void Piece::update(vector<ofImage*> aImages) {
	unsigned char tempImage[120 * 120];
	setActiveBlock(aImages.at(2)->getPixels(0, 0, 120, 120, tempImage), 0, 0);
	setActiveBlock(aImages.at(3)->getPixels(0, 0, 120, 120, tempImage), 0, 1);
	setActiveBlock(aImages.at(4)->getPixels(0, 0, 120, 120, tempImage), 0, 2);
	setActiveBlock(aImages.at(5)->getPixels(0, 0, 120, 120, tempImage), 0, 3);
	setActiveBlock(aImages.at(6)->getPixels(0, 0, 120, 120, tempImage), 1, 0);
	setActiveBlock(aImages.at(7)->getPixels(0, 0, 120, 120, tempImage), 1, 1);
	setActiveBlock(aImages.at(8)->getPixels(0, 0, 120, 120, tempImage), 1, 2);
	setActiveBlock(aImages.at(9)->getPixels(0, 0, 120, 120, tempImage), 1, 3);
	setActiveBlock(aImages.at(10)->getPixels(0, 0, 120, 120, tempImage), 2, 0);
	setActiveBlock(aImages.at(11)->getPixels(0, 0, 120, 120, tempImage), 2, 1);
	setActiveBlock(aImages.at(12)->getPixels(0, 0, 120, 120, tempImage), 2, 2);
	setActiveBlock(aImages.at(13)->getPixels(0, 0, 120, 120, tempImage), 2, 3);
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
	// check for upside L to start a game
	if(blocks[0][0] && blocks[1][0] && blocks[2][0] &&
	   blocks[2][1] && blocks[2][2] && blocks[2][3] &&
	   !blocks[0][1] && !blocks[1][1] && !blocks[0][2] &&
	   !blocks[1][1] && !blocks[1][2] && !blocks[1][3]) {
		   return true;
	}
	else {
		return false;
	}
	//// check for cross to start a game
	//if(blocks[1][0] && blocks[0][1] &&
	//   blocks[1][1] && blocks[2][1] && 
	//   blocks[1][2] && blocks[1][3] &&
	//   !blocks[0][0] && !blocks[2][0] &&
	//   !blocks[0][2] && !blocks[2][2] &&
	//   !blocks[0][3] && !blocks[2][3]) {
	//	return true;
	//}
	//else {
	//	return false;
	//}
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
		sensitivity = PIECE_WIDTH * PIECE_HEIGHT;
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
		blocks[aCol][aRow] = true; 
		return;
	} 
	else {
		blocks[aCol][aRow] = false;
	}
}
