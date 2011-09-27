#ifndef _GAME_CORE
#define _GAME_CORE

#include "ofMain.h"
#include "Kinect.h"
#include "gameSound.h"
#include "userImput.h"
#include "gameLogic.h"
#include "graficEngine.h"
//#include "gameImages.h"

#define GAMESCREENX 190
#define GAMESCREENY 0
#define GAMESCREENWIDTH	10 // in blocks
#define GAMESCREENHEIGHT 18 // in blocks
#define SILHOUETTESCREENX 730
#define SILHOUETTESCREENY 50
#define SILHOUETTEBLOCKSIZE 110
#define RECOSCREENX 670
#define RECOSCREENY 50
#define RECOBLOCKSIZE 150 
#define BLOCKSIZE 40
#define PIECEWIDTH 3 // in blocks
#define PIECEHEIGHT 4 // in blocks
#define LEFT 0 
#define RIGHT 1

class GameCore : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void windowResized(int w, int h);

	GameSound gameSound;
	GameLogic gameLogic;
	UserImput userImput;
	GraficEngine graficEngine;
//	GameImages gameImages;

private:
	void loadExternalData();

	void switchMode(int mode);

	void clearPieceBlocks(bool blocks[PIECEWIDTH][PIECEHEIGHT]);
	void clearGameBlocks(int blocks[GAMESCREENWIDTH][GAMESCREENHEIGHT]);
	void updateDepthStream();
	void setActiveBlock(unsigned char* pixels, int line, int col);
	void checkActiveBlocks();
	void setPieceBlocks();
	void updateGameScreen();
	void resetGame();
	bool isPossibleMove(int line, int column);
	bool isGameOver();
	void setMoveBlock(unsigned char* pixels, int direction);
	void deleteLine(int pY);
	void deletePossibleLines();
	void storePiece(int stone);

	void drawBG();
	void drawSilhouette(int x, int y, int size);
	void drawBoard();
	void drawPiece();
	void drawGameOverZone();
	void drawScore();

	int calcScore();
	int addUpScore(int line);

	// game states
	bool isIdleMode;
	bool isRecoMode;
	bool isGameMode;
	bool isOverMode;

	// game variables
	bool clearScreen;
	bool moveLeft;
	bool moveRight;
	bool activeBlocks[PIECEWIDTH][PIECEHEIGHT]; // block layover over silhouette
	bool pieceBlocks[PIECEWIDTH][PIECEHEIGHT]; // moving piece in the game
	bool lastPieceBlocks[PIECEWIDTH][PIECEHEIGHT]; // last moving piece in the game
	int gameBlocks[GAMESCREENWIDTH][GAMESCREENHEIGHT]; // game board
	int lastGameBlocks[GAMESCREENWIDTH][GAMESCREENHEIGHT]; // last game board
	int gameSpeed;
	int prevTime;
	int blockSpeed; // in ms
	int pieceX;
	int pieceY;
	int highscore;
	int lasthighscore;
	int complexCalc;
	float complexCalcR0;
	float complexCalcR1;
	float complexCalcR2;
	float complexCalcR3;
	
	//images
	ofImage	imgLogo;
	ofImage	imgCopyright;
	ofImage	imgLeftWall;
	ofImage	imgRightWall;
	ofImage	imgScoreBG;
	ofImage imgB1; // 40x40 px block
	ofImage imgB2; // 40x40 px block
	ofImage imgB3; // 40x40 px block
	ofImage imgB4; // 40x40 px block
	ofImage imgB5; // 40x40 px block
	ofImage imgB6; // 40x40 px block
	ofImage imgRecoLabel;
	ofImage imgGameLabel;
	ofImage imgOverLabel;
	ofImage imgOutline;

	//font
	ofTrueTypeFont font; // should still be changed to "gunship bitmap"

	//
	ofImage depthMask;
	ofImage	depthStream;
	Kinect* kinect;
	int nearThreshold; // distance in mm
	int farThreshold; // distance in mm
};

#endif
