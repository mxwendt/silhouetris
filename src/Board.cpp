#include "Board.h"

///////////////////////////////////////////////////////////////
Board::Board() {
	imgB1.loadImage("b1.jpg");
	imgB2.loadImage("b2.jpg");
	imgB3.loadImage("b3.jpg");
	imgB4.loadImage("b4.jpg");
	imgB5.loadImage("b5.jpg");
	imgB6.loadImage("b6.jpg");

	imgB1Dummy.loadImage("b1-dummy.png");

	// clear blocks
	for(int i = 0; i < BOARD_COLUMNS; i++) {
		for(int j = 0; j < BOARD_ROWS; j++) {
			blocks[i][j] = 0;
		}
	}

	initialBlocksType = 1;

	pieceX = 3;
	pieceY = 0;

	clearScreen = false;
}

Board::~Board() {}

///////////////////////////////////////////////////////////////
void Board::draw(Piece* aPiece) {
	// draw blocks on board
	ofSetColor(255, 255, 255);
	for(int i = 0; i < BOARD_COLUMNS; i++) {
		for(int j = 0; j < BOARD_ROWS; j++) {
			if(clearScreen) {
				if(blocks[i][j] == 0) {
					ofRect(i * BLOCK_SIZE + 37,
					       j * BLOCK_SIZE + 0, BLOCK_SIZE, BLOCK_SIZE);
				}
			}
			if(blocks[i][j] == 1) {
				imgB1.draw(i * BLOCK_SIZE + 37, j * BLOCK_SIZE + 0);
			} 
			else if(blocks[i][j] == 2) {
				imgB2.draw(i * BLOCK_SIZE + 37, j * BLOCK_SIZE + 0);
			} 
			else if(blocks[i][j] == 3) {
				imgB3.draw(i * BLOCK_SIZE + 37, j * BLOCK_SIZE + 0);
			}
			else if(blocks[i][j] == 4) {
				imgB4.draw(i * BLOCK_SIZE + 37, j * BLOCK_SIZE + 0);
			} 
			else if(blocks[i][j] == 5) {
				imgB5.draw(i * BLOCK_SIZE + 37, j * BLOCK_SIZE + 0);
			} 
			else if(blocks[i][j] == 6) {
				imgB6.draw(i * BLOCK_SIZE + 37, j * BLOCK_SIZE + 0);
			}
		}
	}
	clearScreen = false;

	// draw piece
	aPiece->drawPiece(37 + pieceX * 40, 0 + pieceY * 40, 120, 160);
}

void Board::drawPieceColumn() {
	ofEnableAlphaBlending();
	ofSetColor(186, 205, 54, 80);
	ofRect(37 + pieceX * 40, 0, 120, 760);
	ofDisableAlphaBlending();
}

void Board::drawInitialBlocks() {
	if(initialBlocksType == 1) {
		// OOX
		// XXX
		// OXX
		// OXX
		ofEnableAlphaBlending();
		ofSetColor(255, 255, 255, 80);
		imgB1Dummy.draw(3 * BLOCK_SIZE + 37, 1 * BLOCK_SIZE + 0);
		imgB1Dummy.draw(4 * BLOCK_SIZE + 37, 1 * BLOCK_SIZE + 0);
		imgB1Dummy.draw(4 * BLOCK_SIZE + 37, 2 * BLOCK_SIZE + 0);
		imgB1Dummy.draw(4 * BLOCK_SIZE + 37, 3 * BLOCK_SIZE + 0);
		imgB1Dummy.draw(5 * BLOCK_SIZE + 37, 0 * BLOCK_SIZE + 0);
		imgB1Dummy.draw(5 * BLOCK_SIZE + 37, 1 * BLOCK_SIZE + 0);
		imgB1Dummy.draw(5 * BLOCK_SIZE + 37, 2 * BLOCK_SIZE + 0);
		imgB1Dummy.draw(5 * BLOCK_SIZE + 37, 3 * BLOCK_SIZE + 0);
		ofDisableAlphaBlending();
	}
	else if(initialBlocksType == 2) {
		// OXO
		// XXX
		// OXO
		// OXO
		ofEnableAlphaBlending();
		ofSetColor(255, 255, 255, 80);
		imgB1Dummy.draw(3 * BLOCK_SIZE + 37, 1 * BLOCK_SIZE + 0);
		imgB1Dummy.draw(4 * BLOCK_SIZE + 37, 0 * BLOCK_SIZE + 0);
		imgB1Dummy.draw(4 * BLOCK_SIZE + 37, 1 * BLOCK_SIZE + 0);
		imgB1Dummy.draw(4 * BLOCK_SIZE + 37, 2 * BLOCK_SIZE + 0);
		imgB1Dummy.draw(4 * BLOCK_SIZE + 37, 3 * BLOCK_SIZE + 0);
		imgB1Dummy.draw(5 * BLOCK_SIZE + 37, 1 * BLOCK_SIZE + 0);
		ofDisableAlphaBlending();
	}
	else if(initialBlocksType == 3) {
		// XXX
		// OOX
		// OOX
		// OOX
		ofEnableAlphaBlending();
		ofSetColor(255, 255, 255, 80);
		imgB1Dummy.draw(3 * BLOCK_SIZE + 37, 0 * BLOCK_SIZE + 0);
		imgB1Dummy.draw(4 * BLOCK_SIZE + 37, 0 * BLOCK_SIZE + 0);
		imgB1Dummy.draw(5 * BLOCK_SIZE + 37, 0 * BLOCK_SIZE + 0);
		imgB1Dummy.draw(5 * BLOCK_SIZE + 37, 1 * BLOCK_SIZE + 0);
		imgB1Dummy.draw(5 * BLOCK_SIZE + 37, 2 * BLOCK_SIZE + 0);
		imgB1Dummy.draw(5 * BLOCK_SIZE + 37, 3 * BLOCK_SIZE + 0);
		ofDisableAlphaBlending();
	}
	else if(initialBlocksType == 4) {
		// OOO
		// OOO
		// XXO
		// XXO
		ofEnableAlphaBlending();
		ofSetColor(255, 255, 255, 80);
		imgB1Dummy.draw(3 * BLOCK_SIZE + 37, 2 * BLOCK_SIZE + 0);
		imgB1Dummy.draw(3 * BLOCK_SIZE + 37, 3 * BLOCK_SIZE + 0);
		imgB1Dummy.draw(4 * BLOCK_SIZE + 37, 2 * BLOCK_SIZE + 0);
		imgB1Dummy.draw(4 * BLOCK_SIZE + 37, 3 * BLOCK_SIZE + 0);
		ofDisableAlphaBlending();
	}
}

void Board::drawBottomRow() {
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255, 80);
	imgB1Dummy.draw(0 * BLOCK_SIZE + 37, 18 * BLOCK_SIZE + 0);
	imgB1Dummy.draw(1 * BLOCK_SIZE + 37, 18 * BLOCK_SIZE + 0);
	imgB1Dummy.draw(2 * BLOCK_SIZE + 37, 18 * BLOCK_SIZE + 0);
	imgB1Dummy.draw(3 * BLOCK_SIZE + 37, 18 * BLOCK_SIZE + 0);
	imgB1Dummy.draw(4 * BLOCK_SIZE + 37, 18 * BLOCK_SIZE + 0);
	imgB1Dummy.draw(5 * BLOCK_SIZE + 37, 18 * BLOCK_SIZE + 0);
	imgB1Dummy.draw(6 * BLOCK_SIZE + 37, 18 * BLOCK_SIZE + 0);
	imgB1Dummy.draw(7 * BLOCK_SIZE + 37, 18 * BLOCK_SIZE + 0);
	imgB1Dummy.draw(8 * BLOCK_SIZE + 37, 18 * BLOCK_SIZE + 0);
	imgB1Dummy.draw(9 * BLOCK_SIZE + 37, 18 * BLOCK_SIZE + 0);
	ofDisableAlphaBlending();
}

bool Board::isGameOver() {
	// if the first line has blocks then the game is over
	for(int i = 0; i < BOARD_COLUMNS; i++) {
		if(blocks[i][3] > 0) {
			return true;
		}
	}
	return false;
}

bool Board::isPossibleMove(Piece* aPiece, int aPieceX, int aPieceY) {
	for(int i1 = pieceX + aPieceX, i2 = 0; i1 < pieceX  + aPieceX + Piece::PIECE_COLUMNS; i1++, i2++) {
		for(int j1 = pieceY + aPieceY, j2 = 0; j1 < pieceY + aPieceY + Piece::PIECE_ROWS; j1++, j2++) {
			// check if the piece is outside the limits of the board
			if(i1 < 0 || i1 > BOARD_COLUMNS - 1 || j1 > BOARD_ROWS - 1) {	
				if(aPiece->isActiveBlock(i2, j2)) {
					return false;
				}
			}

			// check for collision with other blocks
			if (j1 >= 0) {
				if(aPiece->isActiveBlock(i2, j2) && blocks[i1][j1] > 0) {
					return false;
				}
			}
		}
	}

	// no collision
	pieceX += aPieceX;
	pieceY += aPieceY;
	return true;
}

void Board::storePiece(Piece* aPiece, int aValue) {
	for(int i1 = pieceX, i2 = 0; i1 < pieceX + Piece::PIECE_COLUMNS; i1++, i2++) {
		for(int j1 = pieceY, j2 = 0; j1 < pieceY + Piece::PIECE_ROWS; j1++, j2++) {
			if(aPiece->isActiveBlock(i2, j2)) {
				blocks[i1][j1] = aValue;
			}
		}
	}
}

int Board::deleteLines() {
	int lineScore = 0;
	for(int j = 0; j < BOARD_ROWS; j++) {
		int i = 0;
		while(i < BOARD_COLUMNS) {
			if(blocks[i][j] == 0) {
				break;
			}
			i++;
		}
		if(i == BOARD_COLUMNS) {
			clearScreen = true;
			int tempScore = 0;
			for(int i = 0; i < BOARD_COLUMNS; i++) {
				tempScore += (blocks[i][j] * 5);
			}
			lineScore += tempScore;	
			// moves all the upper lines, except the first 4 startrows, one row down
			for(int m = j; m > 3; m--) {
				for(int n = 0; n < BOARD_COLUMNS; n++) {
					blocks[n][m] = blocks[n][m-1];
				}
			}
		}
	}
	return lineScore;
}

void Board::setInitialBlocks(int aType) {
	initialBlocksType = aType;
}

int Board::getInitialBlocks() {
	return initialBlocksType;
}

void Board::insertNewPiece() {
	pieceY = 0;
}

void Board::centerPiece() {
	pieceX = 3;
	pieceY = 0;
}

void Board::reset() {
	// clear blocks
	for(int i = 0; i < BOARD_COLUMNS; i++) {
		for(int j = 0; j < BOARD_ROWS; j++) {
			blocks[i][j] = 0;
		}
	}

	pieceX = 3;
	pieceY = 0;
}