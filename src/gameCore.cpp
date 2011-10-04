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
	elapsedTimeForGameSpeed = 0;

	changeState(IDLE_STATE);
}

void GameCore::exit() {
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
			changeState(PLAY_STATE);
		}
		break;
	case PLAY_STATE:
		kinect->updateDepthImage();
		piece->update(kinect->getDepthImage());
		if(ofGetElapsedTimeMillis() - elapsedTimeForDisplayUpdate > blockSpeed) {
			if(!piece->isEmpty()) {
				// check if move right is possible
				if(piece->isMoveRight()) {
					board->isPossibleMove(piece, 1, 0);
				}
				// check if move left is possible
				if(piece->isMoveLeft()) {
					board->isPossibleMove(piece, -1, 0);
				}
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
						blockSpeed = 1000;

						changeState(OVER_STATE);
					}
					checkElapsedTime();
				}
			}
			elapsedTimeForDisplayUpdate = ofGetElapsedTimeMillis();
		}
		break;
	case OVER_STATE:
		kinect->updateDepthImage();
		piece->update(kinect->getDepthImage());
		if(piece->isCross()) {
			changeState(PLAY_STATE);
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
		changeState(PLAY_STATE);
		break;
	case '4':  
		changeState(OVER_STATE);
		break;
	/*case '5': 
		deleteLine(18); 
		break;*/
	case '6':
		sound.increaseIdleMusicVol(0.1f);
		break;
	case '5':
		sound.decreaseIdleMusicVol(0.1f);
		break;
	case '8':
		sound.increaseRecoMusicVol(0.1f);
		break;
	case '7':
		sound.decreaseRecoMusicVol(0.1f);
		break;
	case '0':
		sound.increasePlayMusicVol(0.1f);
		break;
	case '9':
		sound.decreasePlayMusicVol(0.1f);
		break;
	case 'b':
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
	// decrease the time in s wich it thakes to the next level
	case 'q':	
		timeToLevelUp -= 10;
		break;	
	// increase the time in s wich it thakes to the next level
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
	default:
		break;
	}
}

///////////////////////////////////////////////////////////////
void GameCore::changeState(int aState) {
	sound.stopPlayingMusic();

	switch(aState) {
	case IDLE_STATE:
		state = IDLE_STATE;
		sound.playIdleMusic();
		break;
	case RECO_STATE:
		state = RECO_STATE;
		sound.playRecoMusic();
		break;
	case PLAY_STATE:
		state = PLAY_STATE;
		sound.playPlayMusic();
		break;
	case OVER_STATE:
		state = OVER_STATE;
		sound.playIdleMusic();
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
