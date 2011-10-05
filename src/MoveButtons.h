#ifndef _MOVE_BUTTONS
#define _MOVE_BUTTONS

#include "ofMain.h"

class MoveButtons {
public:
	///////////////////////////////////////////////////////////////
	MoveButtons();
	~MoveButtons();

	///////////////////////////////////////////////////////////////
	void update(vector<ofImage*> aImages);

	void drawMoveButtons(int aX, int aY);

	bool isMoveLeft();
	bool isMoveRight();

	void changeSensitivity(int aValue);

private:
	///////////////////////////////////////////////////////////////
	static const int LEFT = 1;
	static const int RIGHT = 2;

	void setMoveBlock(unsigned char* aPixels, int aDir);

	bool moveLeft;
	bool moveRight;
	/*bool lastMoveLeft;
	bool lastMoveRight;*/

	int sensitivity; // pixel count that makes a block active
};

#endif
