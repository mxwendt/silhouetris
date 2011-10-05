#ifndef _SCORE
#define _SCORE

#include "Piece.h"
#include "ofMain.h"

class Score {
public:
	///////////////////////////////////////////////////////////////
	Score();
	~Score();

	///////////////////////////////////////////////////////////////
	void update(int aValue);
	void draw(int aX, int aY);

	void drawCounter(int aX, int aY, int aValue);

	int calcScore(Piece* aPiece);
	void reset();

private:
	///////////////////////////////////////////////////////////////
	float complexCalcR0;
	float complexCalcR1;
	float complexCalcR2;
	float complexCalcR3;
	int complexCalc;
	int highscore;

	ofTrueTypeFont font; // should still be changed to "gunship bitmap"
};

#endif
