#include "GameCore.h"

///////////////////////////////////////////////////////////////
void GameCore::setup() {
	ofBackground(39, 40, 32);

	sound.loadSoundFiles();

	piece = new Piece();
	board = new Board();
	score = new Score();
	kinect = new Kinect(1500, 3000);

	blockSpeed = 1000;
	timeToLevelUp = 60;
	speedIncreaseLevel = 200;

	changeState(IDLE_STATE);
}

void GameCore::exit() {
	// clean up
	delete piece;
	piece = NULL;
	
	delete board;
	board = NULL;

	delete score;
	score = NULL;

	delete kinect;
	kinect = NULL;
}

void GameCore::update() {
	switch(state) {
	case IDLE_STATE:
		kinect->updateDepthImage();
		piece->update(kinect->getDepthImage());
		if(!piece->isEmpty()) {
			changeState(RECO_STATE);
		}
		break;
	case RECO_STATE:
		kinect->updateDepthImage();
		piece->update(kinect->getDepthImage());
		if(piece->isCross()) {
			changeState(MOVE_STATE);
		}
		break;
	case MOVE_STATE:
		kinect->updateDepthImage();
		piece->update(kinect->getDepthImage());
		if(ofGetElapsedTimeMillis() - elapsedTimeForDisplayUpdate > 500) {
			if(!piece->isEmpty()) {
				// check if move right is possible
				if(piece->isMoveRight()) {
					board->isPossibleMove(piece, 1, 0);
				}
				// check if move left is possible
				if(piece->isMoveLeft()) {
					board->isPossibleMove(piece, -1, 0);
				}
				elapsedTimeForDisplayUpdate = ofGetElapsedTimeMillis();
				moveCounter++;
			}

			if(moveCounter > 8) {
				changeState(PLAY_STATE);
			}
		}
		break;
	case PLAY_STATE:
		kinect->updateDepthImage();
		piece->update(kinect->getDepthImage());
		if(ofGetElapsedTimeMillis() - elapsedTimeForDisplayUpdate > blockSpeed) {
			if(!piece->isEmpty()) {
				// check if move down is possible
				if(!board->isPossibleMove(piece, 0, 1)) {
					board->storePiece(piece, score->calcScore(piece));
					sound.playSoundHitBottom();
					score->update(board->deleteLines());
					sound.playSoundClearLine();
					board->insertNewPiece();
					if(board->isGameOver()) {
						board->reset();
						piece->reset();
						score->reset();
						changeState(OVER_STATE);
					}
					checkElapsedTime();
					changeState(MOVE_STATE);
				}
			}
			elapsedTimeForDisplayUpdate = ofGetElapsedTimeMillis();
		}
		break;
	case OVER_STATE:
		kinect->updateDepthImage();
		piece->update(kinect->getDepthImage());
		if(piece->isCross()) {
			changeState(MOVE_STATE);
		}
		break;
	default:
		break;
	}
}

void GameCore::draw() {
	switch(state) {
	case IDLE_STATE:
		images.drawIdleState();
		break;
	case RECO_STATE:
		images.drawRecoState();
		kinect->drawDepthImage(499, 24, 500, 480);
		piece->drawOverlay(569, 24, 360, 480);
		board->draw(piece);
		score->draw(499, 695);
		break;
	case MOVE_STATE:
		images.drawPlayState();
		kinect->drawDepthImage(499, 24, 500, 480);
		piece->drawMoveButtons(569, 24);
		board->draw(piece);
		score->draw(499, 695);
		break;
	case PLAY_STATE:
		images.drawPlayState();
		kinect->drawDepthImage(499, 24, 500, 480);
		piece->drawOverlay(569, 24, 360, 480);
		board->draw(piece);
		score->draw(499, 695);
		break;
	case OVER_STATE:
		images.drawOverState();
		kinect->drawDepthImage(499, 24, 500, 480);
		piece->drawOverlay(569, 24, 360, 480);
		board->draw(piece);
		score->draw(499, 695);
		break;
	default:
		break;
	}
}

void GameCore::keyPressed(int aKey) {
	switch (aKey) {
	case '1': 
		changeState(IDLE_STATE);
		break;
	case '2': 
		changeState(RECO_STATE);
		break;
	case '3': 
		changeState(MOVE_STATE);
		break;
	case '4':  
		changeState(PLAY_STATE);
		break;
	case '5':  
		changeState(OVER_STATE);
		break;
	case 'a':
		sound.increaseIdleMusicVol(0.1f);
		break;
	case 's':
		sound.decreaseIdleMusicVol(0.1f);
		break;
	case 'd':
		sound.increaseRecoMusicVol(0.1f);
		break;
	case 'f':
		sound.decreaseRecoMusicVol(0.1f);
		break;
	case 'g':
		sound.increasePlayMusicVol(0.1f);
		break;
	case 'h':
		sound.decreasePlayMusicVol(0.1f);
		break;
	case 'j':
		sound.stopPlayingMusic();
		break;
	// increase threshold to the front
	case 'n':
		kinect->changeThreshold(50, 0);	
		break;	
	// decrease threshold to the front
	case 'm':
		kinect->changeThreshold(-50, 0);
		break;
	// increase threshold to the back
	case ',':
		kinect->changeThreshold(0, 50);
		break;
	// decrease threshold to the back
	case '.':
		kinect->changeThreshold(0, -50);
		break;
	// decrease time in s which it takes to the next level
	case 'q':	
		timeToLevelUp -= 10;
		break;	
	// increase time in s which it takes to the next level
	case 'w':
		timeToLevelUp += 10;
		break;
	// decrease time in ms how big the increase of "blockSpeed" per level is
	case 'e':	
		speedIncreaseLevel -= 10;
		break;	
	// increase time in ms how big the increase of "blockSpeed" per level is
	case 'r':
		speedIncreaseLevel += 10;
		break;
	// decrease pixels it takes to activate a block for the piece
	case 'k':
		piece->changeSensitivity(-10);
		break;
	// increase pixels it takes to activate a block for the piece
	case 'l':
		piece->changeSensitivity(10);
		break;
	default:
		break;
	}
}

///////////////////////////////////////////////////////////////
void GameCore::changeState(int aState) {
	sound.stopPlayingMusic();

	switch(aState) {
	case IDLE_STATE:
		cout << "IDLE_STATE" << endl;
		state = IDLE_STATE;
		sound.playIdleMusic();
		break;
	case RECO_STATE:
		cout << "RECO_STATE" << endl;
		state = RECO_STATE;
		sound.playRecoMusic();
		break;
	case MOVE_STATE:
		cout << "MOVE_STATE" << endl;
		state = MOVE_STATE;
		sound.playPlayMusic();
		moveCounter = 0;
		elapsedTimeForDisplayUpdate = ofGetElapsedTimeMillis();
		break;
	case PLAY_STATE:
		cout << "PLAY_STATE" << endl;
		state = PLAY_STATE;
		sound.playPlayMusic();
		elapsedTimeForDisplayUpdate = ofGetElapsedTimeMillis();
		break;
	case OVER_STATE:
		cout << "OVER_STATE" << endl;
		state = OVER_STATE;
		sound.playIdleMusic();
		blockSpeed = 1000;
		break;
	default:
		break;
	}
}

void GameCore::checkElapsedTime() {
	if(ofGetElapsedTimef() - elapsedTimeForGameSpeed >= timeToLevelUp) {
		blockSpeed -= speedIncreaseLevel;
		elapsedTimeForGameSpeed = ofGetElapsedTimef();
	}
}
