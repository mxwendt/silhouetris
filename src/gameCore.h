#ifndef _GAME_CORE
#define _GAME_CORE

#include "GameSound.h"
#include "GameImages.h"
#include "Piece.h"
#include "MoveButtons.h"
#include "Board.h"
#include "Score.h"
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
	GameSound sound;
	GameImages images;

	Piece* piece;
	MoveButtons* buttons;
	Board* board;
	Score* score;
	Kinect* kinect;

	int moveCounter;

	int elapsedTimeForDisplayUpdate; // in ms
	int elapsedTimeForGameSpeed; // in s
	int timeToLevelUp; // time in s which it thakes to the next level
	int speedIncreaseLevel; // time in ms how big the increase of "blockSpeed" per level is
	int blockSpeed; // ms that it takes to move a piece one step down
};

#endif
