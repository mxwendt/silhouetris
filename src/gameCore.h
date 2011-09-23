#ifndef _GAME_CORE
#define _GAME_CORE

#include "ofMain.h"
#include "ofxOpenNI.h"


#define GAMESCREENX			190
#define GAMESCREENY			0
#define GAMESCREENWIDTH		10 // in blocks
#define GAMESCREENHEIGHT	18 // in blocks
#define SILHOUETTESCREENX	730
#define SILHOUETTESCREENY	50
#define SILHOUETTEBLOCKSIZE 110
#define RECOSCREENX			670
#define RECOSCREENY			50
#define RECOBLOCKSIZE		150 
#define BLOCKSIZE			40
#define PIECEWIDTH			3 // in blocks
#define PIECEHEIGHT			4 // in blocks

#define LEFT	0 
#define RIGHT	1


class gameCore : public ofBaseApp {
	
public:
	
	//--------------------------------------------------------------
															// SETUP 
	void setup();
	void loadExternalData();
	void startKinect();

	/* kinect variables */

	ofxOpenNIContext  streamContext;
	ofxDepthGenerator streamDepth; // image from depth camera

	ofImage	depthStream;	// depth info
	ofImage	depthRangeMask; // depth info in a defined range
	int		nearThreshold;	// distance in mm
	int		farThreshold;	// distance in mm

	/* graphics variables */

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

	/* sound variables */

	ofSoundPlayer soundLine;
	ofSoundPlayer soundHit;
	ofSoundPlayer soundOver;
	ofSoundPlayer soundIdle;
	ofSoundPlayer soundReco;
	ofSoundPlayer soundGame;

	float idleSoundVol;
	float recoSoundVol;
	float gameSoundVol;

	//--------------------------------------------------------------
														   // UPDATE
	void update();

	void updateIdleMode();
	void updateRecoMode();
	void updateGameMode();
	void updateOverMode();
	
	void updateDepthStream();
	void updateGameScreen();

	void switchMode(int mode);


	//--------------------------------------------------------------
															 // DRAW
	void draw();
	
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

	
	//--------------------------------------------------------------
															// LOGIC
	void resetGame();
	void setActiveBlock(unsigned char* pixels, int line, int col);
	void setMoveBlock(unsigned char* pixels, int direction);
	void setPieceBlocks();
	void checkActiveBlocks();
	void clearPieceBlocks(bool blocks[PIECEWIDTH][PIECEHEIGHT]);
	void clearGameBlocks(int blocks[GAMESCREENWIDTH][GAMESCREENHEIGHT]);
	void deleteLine (int pY);
	void deletePossibleLines();

	int calcScore();
	int addUpScore(int line);
	
	bool isGameOver();
	bool isFreeBlock(int line, int column);
	bool isPossibleMove(int line, int column);
	int  getXPosOnBoard(int column);
	int  getYPosOnBoard(int line);
	void storePiece(int stone);

	/* app variables */

	bool isIdleMode;
	bool isRecoMode;
	bool isGameMode;
	bool isOverMode;

	int	prevTime;

	/* game variables */

	bool activeBlocks[PIECEWIDTH][PIECEHEIGHT]; // block layover over silhouette
	bool pieceBlocks[PIECEWIDTH][PIECEHEIGHT]; // moving piece in the game
	bool lastPieceBlocks[PIECEWIDTH][PIECEHEIGHT]; // last moving piece in the game
	
	int gameBlocks[GAMESCREENWIDTH][GAMESCREENHEIGHT]; // game board
	int	lastGameBlocks[GAMESCREENWIDTH][GAMESCREENHEIGHT]; // last game board
	
	bool clearScreen;
	bool moveLeft;
	bool moveRight;
	int	 gameSpeed;
	int	 blockSpeed; // in ms
	int	 pieceX;
	int	 pieceY;

	int	  highscore;
	int	  lasthighscore;
	int	  complexCalc;
	float complexCalcR0;
	float complexCalcR1;
	float complexCalcR2;
	float complexCalcR3;
		
	
	//--------------------------------------------------------------
													   // USER INPUT
	void keyPressed(int key);
	/*void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);*/

};

#endif
