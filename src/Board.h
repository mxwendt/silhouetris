#ifndef _BOARD
#define _BOARD

#include "Piece.h"
#include "ofMain.h"

class Board {
public:
	///////////////////////////////////////////////////////////////
	Board();
	~Board();

	///////////////////////////////////////////////////////////////
	void update(Piece* aPiece);
	void draw(Piece* aPiece);

	bool isGameOver();

	bool isPossibleMove(Piece* aPiece, int aPieceX, int aPieceY);
	void storePiece(Piece* aPiece, int aValue);
	int deleteLines();
	
	void insertNewPiece();
	void reset();

private:
	///////////////////////////////////////////////////////////////
	static const int BOARD_COLUMNS = 10; // in blocks
	static const int BOARD_ROWS = 19; // in blocks
	static const int BLOCK_SIZE = 40;

	int blocks[BOARD_COLUMNS][BOARD_ROWS];

	ofImage imgB1; // 40x40 px block
	ofImage imgB2; // 40x40 px block
	ofImage imgB3; // 40x40 px block
	ofImage imgB4; // 40x40 px block
	ofImage imgB5; // 40x40 px block
	ofImage imgB6; // 40x40 px block

	int pieceX;
	int pieceY;

	bool clearScreen;
};

#endif
