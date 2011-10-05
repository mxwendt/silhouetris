#include "GameImages.h"

///////////////////////////////////////////////////////////////
GameImages::GameImages() {
	logo.loadImage("logo.png");
	copyright.loadImage("copyright.png");
	wallLeft.loadImage("wallLeft.png");
	wallRight.loadImage("wallRight.png");
	score.loadImage("score.png");

	outMoveLeft.loadImage("outlineMoveLeft.png");
	outMoveRight.loadImage("outlineMoveRight.png");
	outMoveTop.loadImage("outlineMoveTop.png");
	outMoveBottom.loadImage("outlineMoveBottom.png");
	outMoveSepLeft.loadImage("outlineMoveSepLeft.png");
	outMoveSepRight.loadImage("outlineMoveSepRight.png");

	outPlayLeft.loadImage("outlinePlayLeft.png");
	outPlayRight.loadImage("outlinePlayRight.png");
	outPlayTop.loadImage("outlinePlayTop.png");
	outPlayBottom.loadImage("outlinePlayBottom.png");
}

GameImages::~GameImages() {
}

///////////////////////////////////////////////////////////////
void GameImages::drawIdleState() {
	ofSetColor(255, 255, 255);
	logo.draw(127, 248);
	copyright.draw(308, 690);
}

void GameImages::drawRecoState() {
	ofSetColor(255, 255, 255);
	ofRect(37, 0, 400, 760);
	wallLeft.draw(0, 0);
	wallRight.draw(437, 0);
	score.draw(474, 551);
}

void GameImages::drawMoveState() {
	ofSetColor(255, 255, 255);
	ofRect(37, 0, 400, 760);
	wallLeft.draw(0, 0);
	wallRight.draw(437, 0);
	score.draw(474, 551);
}

void GameImages::drawPlayState() {
	ofSetColor(255, 255, 255);
	ofRect(37, 0, 400, 760);
	wallLeft.draw(0, 0);
	wallRight.draw(437, 0);
	score.draw(474, 551);
}

void GameImages::drawOverState() {
	ofSetColor(255, 255, 255);
	ofRect(37, 0, 400, 760);
	wallLeft.draw(0, 0);
	wallRight.draw(437, 0);
	score.draw(474, 551);
}

void GameImages::drawOutline(bool aSeperator) {
	ofSetColor(255, 255, 255);
	if(!aSeperator) {
		outPlayLeft.draw(561, 13);
		outPlayRight.draw(929, 13);
		outPlayTop.draw(569, 13);
		outPlayBottom.draw(569, 504);
	}
	else {
		outMoveLeft.draw(491, 13);
		outMoveRight.draw(999, 13);
		outMoveTop.draw(499, 13);
		outMoveBottom.draw(499, 504);
		outMoveSepLeft.draw(569, 24);
		outMoveSepRight.draw(918, 24);
	}
}
