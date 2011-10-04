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
	void drawPlayState();
	void drawOverState();

private:
	///////////////////////////////////////////////////////////////
	ofImage logo;
	ofImage copyright;
	ofImage wallLeft;
	ofImage wallRight;
	ofImage score;
};

#endif
