#ifndef _GAME_CORE
#define _GAME_CORE

#include "GameImages.h"
#include "Piece.h"
#include "MoveButtons.h"
#include "Board.h"
#include "Score.h"
#include "MilliTimer.h"
#include "Kinect.h"
#include "ofMain.h"

typedef enum {
	IDLE_STATE,
	RECO_STATE,
	MOVE_STATE,
	PLAY_STATE,
	OVER_STATE
} GameState;

class GameCore : public ofBaseApp {
public:
	///////////////////////////////////////////////////////////////
	void setup();
	void exit();

	void update();
	void draw();

	void keyPressed(int aKey);

private:
	///////////////////////////////////////////////////////////////
	void changeState(int aState);
	void checkElapsedTime();

	GameState state;
	GameImages images;

	Piece* piece;
	MoveButtons* buttons;
	Board* board;
	Score* score;
	MilliTimer* updateTimer;
	MilliTimer* countTimer;
	Kinect* kinect;

	bool moveLeftActive;
	bool moveRightActive;

	int counter;

	int initialSpeed;
	int initialSpeedIncrease;
	int movePeriod;

	int speed; // millisec it takes to move one row down
};

#endif
