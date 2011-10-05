#ifndef _GAME_IMAGES
#define _GAME_IMAGES

#include "ofMain.h"

class GameImages {
public:
	///////////////////////////////////////////////////////////////
	GameImages();
	~GameImages();

	///////////////////////////////////////////////////////////////
	void drawIdleState();
	void drawRecoState();
	void drawMoveState();
	void drawPlayState();
	void drawOverState();

	void drawOutline(bool aSeperator);

private:
	///////////////////////////////////////////////////////////////
	ofImage logo;
	ofImage copyright;
	ofImage wallLeft;
	ofImage wallRight;
	ofImage score;

	ofImage outMoveLeft;
	ofImage outMoveRight;
	ofImage outMoveTop;
	ofImage outMoveBottom;
	ofImage outMoveSepLeft;
	ofImage outMoveSepRight;

	ofImage outPlayLeft;
	ofImage outPlayRight;
	ofImage outPlayTop;
	ofImage outPlayBottom;
};

#endif
