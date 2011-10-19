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
	void drawGameOverZone();
	void drawHighscore();

	void drawRecoInstructions();
	void drawMoveInstructions();
	void drawPlayInstructions();
	void drawOverInstructions();

private:
	///////////////////////////////////////////////////////////////
	ofImage logo;
	ofImage copyright;
	ofImage wallLeft;
	ofImage wallRight;
	ofImage score;
	ofImage gameOverZone;
	ofImage counter;
	ofImage highscore;

	ofImage outMoveLeft;
	ofImage outMoveRight;
	ofImage outMoveTop;
	ofImage outMoveBottom;
	ofImage outMoveSepLeft;
	ofImage outMoveSepRight;

	ofImage arrowRight;
	ofImage arrowLeft;

	ofImage outPlayLeft;
	ofImage outPlayRight;
	ofImage outPlayTop;
	ofImage outPlayBottom;

	ofImage instrBuildRows;
	ofImage instrActivateBlocks;
	ofImage instrInitialBlocks;
	ofImage instrMoveLeft;
	ofImage instrMoveRight;	
};

#endif
