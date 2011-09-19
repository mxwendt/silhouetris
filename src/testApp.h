#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"


#define GAMESCREENX 190
#define GAMESCREENY 0
#define GAMESCREENWIDTH 10 // in blocks
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


class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void loadExternalData();
	void startKinect();

	void updateIdleMode();
	void updateRecoMode();
	void updateGameMode();
	void updateOverMode();
	void updateDepthStream();
	void updateGameScreen();
	void switchMode(int mode);

	void drawIdleMode();
	void drawRecoMode();
	void drawGameMode();
	void drawOverMode();
	void drawBG();
	void drawSilhouette(int x, int y, int size);
	void drawBoard();
	void drawPiece();
	void drawGameOverZone();
	void drawScore();

	void resetGame();
	void setActiveBlock(unsigned char* pixels, int line, int col);
	void setMoveBlock(unsigned char* pixels, int direction);
	void setPieceBlocks();
	void checkActiveBlocks();
	void clearPieceBlocks(bool blocks[PIECEWIDTH][PIECEHEIGHT]);
	void clearGameBlocks(int blocks[GAMESCREENWIDTH][GAMESCREENHEIGHT]);
	void deleteLine (int pY);
	void deletePossibleLines();
	void storePiece(int stone);
	bool isGameOver();
	bool isFreeBlock(int line, int column);
	bool isPossibleMove(int line, int column);
	int calcScore();
	int addUpScore(int line);
	int getXPosOnBoard(int column);
	int getYPosOnBoard(int line);

	void keyPressed  (int key);

	bool isIdleMode;
	bool isRecoMode;
	bool isGameMode;
	bool isOverMode;
	bool activeBlocks[PIECEWIDTH][PIECEHEIGHT]; // block layover over silhouette
	bool pieceBlocks[PIECEWIDTH][PIECEHEIGHT]; // moving piece in the game
	bool lastPieceBlocks[PIECEWIDTH][PIECEHEIGHT]; // last moving piece in the game
	bool clearScreen;
	bool moveLeft;
	bool moveRight;

	int gameBlocks[GAMESCREENWIDTH][GAMESCREENHEIGHT]; // game board
	int lastGameBlocks[GAMESCREENWIDTH][GAMESCREENHEIGHT]; // last game board
	int gameSpeed;
	int blockSpeed; // in ms
	int pieceX;
	int pieceY;
	int highscore;
	int lasthighscore;
	int complexCalc;
	int prevTime;

	float complexCalcR0;
	float complexCalcR1;
	float complexCalcR2;
	float complexCalcR3;	

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
	
	ofTrueTypeFont font; // should still be changed to "gunship bitmap"

	ofSoundPlayer soundLine;
	ofSoundPlayer soundHit;
	ofSoundPlayer soundOver;
	ofSoundPlayer soundIdle;
	ofSoundPlayer soundReco;
	ofSoundPlayer soundGame;

	float idleSoundVol;
	float recoSoundVol;
	float gameSoundVol;
};

#endif
