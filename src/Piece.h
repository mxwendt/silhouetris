#ifndef _PIECE
#define _PIECE

#include "ofMain.h"

class Piece {
public:
	///////////////////////////////////////////////////////////////
	Piece();
	~Piece();

	///////////////////////////////////////////////////////////////
	static const int PIECE_COLUMNS = 3; // in blocks
	static const int PIECE_ROWS = 4; // in blocks
	static const int PIECE_WIDTH = 120; // in blocks
	static const int PIECE_HEIGHT = 160; // in blocks

	void update(ofImage* aDepthImage);
	void drawOverlay(int aX, int aY, int aWidth, int aHeight);
	void drawMoveButtons(int aX, int aY);
	void drawPiece(int aX, int aY, int aWidth, int aHeight);

	bool isEmpty();
	bool isCross();

	bool isActiveBlock(int aCol, int aRow);
	bool isMoveLeft();
	bool isMoveRight();

	void changeSensitivity(int aValue);

	void reset();

private:
	///////////////////////////////////////////////////////////////
	static const int LEFT = 1;
	static const int RIGHT = 2;

	void setActiveBlock(unsigned char* aPixels, int aCol, int aRow);
	void setMoveBlock(unsigned char* aPixels, int aDir);

	bool blocks[3][4];

	bool moveLeft;
	bool moveRight;
	bool lastMoveLeft;
	bool lastMoveRight;

	int sensitivity; // pixel count that makes a block active
};

#endif
