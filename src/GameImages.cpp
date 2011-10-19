#include "GameImages.h"

///////////////////////////////////////////////////////////////
GameImages::GameImages() {
	logo.loadImage("logo.png");
	copyright.loadImage("copyright.png");
	wallLeft.loadImage("wall-left.png");
	wallRight.loadImage("wall-right.png");
	score.loadImage("score-dutch.png");
	gameOverZone.loadImage("game-over-zone-line.png");
	counter.loadImage("counter.png");
	highscore.loadImage("highscore.png");

	outMoveLeft.loadImage("outlineMoveLeft.png");
	outMoveRight.loadImage("outlineMoveRight.png");
	outMoveTop.loadImage("outlineMoveTop.png");
	outMoveBottom.loadImage("outlineMoveBottom.png");
	outMoveSepLeft.loadImage("outlineMoveSepLeft.png");
	outMoveSepRight.loadImage("outlineMoveSepRight.png");

	arrowLeft.loadImage("arrow-left.png");
	arrowRight.loadImage("arrow-right.png");

	outPlayLeft.loadImage("outlinePlayLeft.png");
	outPlayRight.loadImage("outlinePlayRight.png");
	outPlayTop.loadImage("outlinePlayTop.png");
	outPlayBottom.loadImage("outlinePlayBottom.png");

	instrBuildRows.loadImage("instruction-build-rows-dutch.png");
	instrActivateBlocks.loadImage("instruction-activate-blocks-dutch.png");
	instrInitialBlocks.loadImage("instruction-initial-blocks-dutch.png");
	instrMoveLeft.loadImage("instruction-move-left-dutch.png");
	instrMoveRight.loadImage("instruction-move-right-dutch.png");
}

GameImages::~GameImages() {}

///////////////////////////////////////////////////////////////
void GameImages::drawIdleState() {
	ofSetColor(255, 255, 255);
	logo.draw(336, 270);
	copyright.draw(313, 686);
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
		outMoveSepLeft.draw(558, 24);
		outMoveSepRight.draw(929, 24);
		ofEnableAlphaBlending();
		arrowLeft.draw(520, 222);
		arrowRight.draw(946, 222);
		ofDisableAlphaBlending();
	}
}

void GameImages::drawGameOverZone() {
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255);
	gameOverZone.draw(37, 138);
	ofDisableAlphaBlending();
}

void GameImages::drawHighscore() {
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255);
	highscore.draw(52, 231);
	ofDisableAlphaBlending();
}

void GameImages::drawRecoInstructions() {
	ofSetColor(255, 255, 255);
	instrInitialBlocks.draw(52, 174);
	ofEnableAlphaBlending();
	instrBuildRows.draw(52, 660);
	instrActivateBlocks.draw(634, 33);
	ofDisableAlphaBlending();
}

void GameImages::drawMoveInstructions() {
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255);
	instrMoveLeft.draw(501, 33);
	instrMoveRight.draw(802, 33);
	counter.draw(210, 130);
	ofDisableAlphaBlending();
}

void GameImages::drawPlayInstructions() {
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255);
	instrActivateBlocks.draw(634, 33);
	ofDisableAlphaBlending();
}

void GameImages::drawOverInstructions() {
	ofSetColor(255, 255, 255);
	instrInitialBlocks.draw(52, 174);
	ofEnableAlphaBlending();
	instrBuildRows.draw(52, 660);
	instrActivateBlocks.draw(634, 33);
	ofDisableAlphaBlending();
}
