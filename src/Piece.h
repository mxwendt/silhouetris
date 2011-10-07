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

	void update(vector<ofImage*> aImages);

	void drawOverlay(int aX, int aY, int aWidth, int aHeight);
	void drawPiece(int aX, int aY, int aWidth, int aHeight);

	bool isEmpty();

	bool isInitialBlocks(int aType);

	bool isActiveBlock(int aCol, int aRow);

	void changeSensitivity(int aValue);

	void reset();

private:
	///////////////////////////////////////////////////////////////
	void setActiveBlock(unsigned char* aPixels, int aCol, int aRow);

	bool blocks[3][4];

	int sensitivity; // pixel count that makes a block active
};

#endif
