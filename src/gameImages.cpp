#include "GameImages.h"

///////////////////////////////////////////////////////////////
GameImages::GameImages() {
	logo.loadImage("logo.png");
	copyright.loadImage("copyright.png");
	wallLeft.loadImage("wallLeft.png");
	wallRight.loadImage("wallRight.png");
	score.loadImage("score.png");
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
	ofRect(37, 0, 400, 768);
	wallLeft.draw(0, 0);
	wallRight.draw(437, 0);
	score.draw(474, 551);
}

void GameImages::drawPlayState() {
	ofSetColor(255, 255, 255);
	ofRect(37, 0, 400, 768);
	wallLeft.draw(0, 0);
	wallRight.draw(437, 0);
	score.draw(474, 551);
}

void GameImages::drawOverState() {
	ofSetColor(255, 255, 255);
	ofRect(37, 0, 400, 768);
	wallLeft.draw(0, 0);
	wallRight.draw(437, 0);
	score.draw(474, 551);
}
