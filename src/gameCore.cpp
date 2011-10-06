#include "GameCore.h"

///////////////////////////////////////////////////////////////
void GameCore::setup() {
	ofBackground(39, 40, 32);

	piece = new Piece();
	buttons = new MoveButtons();
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
	
	delete buttons;
	buttons = NULL;

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
		kinect->separateImage();
		piece->update(kinect->getImages());
		if(!piece->isEmpty()) {
			changeState(RECO_STATE);
			break;
		}
		break;
	case RECO_STATE:
		kinect->updateDepthImage();
		kinect->separateImage();
		piece->update(kinect->getImages());
		if(piece->isInitialForm()) {
			changeState(MOVE_STATE);
			break;
		}
		break;
	case MOVE_STATE:
		kinect->updateDepthImage();
		kinect->separateImage();
		buttons->update(kinect->getImages());
		if(ofGetElapsedTimeMillis() - elapsedTimeForDisplayUpdate > 500) {
			if(!piece->isEmpty()) {
				// check if move right is possible
				if(buttons->isMoveRight()) {
					board->isPossibleMove(piece, 1, 0);
				}
				// check if move left is possible
				if(buttons->isMoveLeft()) {
					board->isPossibleMove(piece, -1, 0);
				}
				elapsedTimeForDisplayUpdate = ofGetElapsedTimeMillis();
				moveCounter++;

				if(moveCounter % 2 == 0) {
					counter--;
				}
			}

			if(moveCounter > 9) {
				changeState(PLAY_STATE);
				break;
			}
		}
		break;
	case PLAY_STATE:
		kinect->updateDepthImage();
		kinect->separateImage();
		piece->update(kinect->getImages());
		if(ofGetElapsedTimeMillis() - elapsedTimeForDisplayUpdate >= blockSpeed) {
			if(!piece->isEmpty()) {
				// check if move down is possible
				if(!board->isPossibleMove(piece, 0, 1)) {
					board->storePiece(piece, score->calcScore(piece));
					score->update(board->deleteLines());
					board->insertNewPiece();
					if(board->isGameOver()) {
						changeState(OVER_STATE);
						break;
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
		kinect->separateImage();
		piece->update(kinect->getImages());
		if(piece->isInitialForm()) {
			changeState(MOVE_STATE);
			break;
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
		kinect->drawBlockImages();
		piece->drawOverlay(569, 24, 360, 480);
		images.drawOutline(false);
		board->draw(piece);
		score->draw(509, 695);
		break;
	case MOVE_STATE:
		images.drawPlayState();
		kinect->drawBlockImages();
		kinect->drawButtonImages();
		buttons->drawMoveButtons(569, 24);
		images.drawOutline(true);
		board->draw(piece);
		score->draw(509, 695);
		score->drawCounter(600, 90, counter);
		if(moveCounter % 2 == 0) {
			
		}
		break;
	case PLAY_STATE:
		images.drawPlayState();
		kinect->drawBlockImages();
		piece->drawOverlay(569, 24, 360, 480);
		images.drawOutline(false);
		board->draw(piece);
		score->draw(509, 695);
		break;
	case OVER_STATE:
		images.drawOverState();
		kinect->drawBlockImages();
		piece->drawOverlay(569, 24, 360, 480);
		images.drawOutline(false);
		board->draw(piece);
		score->draw(509, 695);
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
		board->reset();
		score->reset();
		changeState(MOVE_STATE);
		break;
	case '4':  
		changeState(PLAY_STATE);
		break;
	case '5':  
		changeState(OVER_STATE);
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
	// decrease pixels it takes to activate a block or button
	case 'k':
		piece->changeSensitivity(-10);
		buttons->changeSensitivity(-10);
		break;
	// increase pixels it takes to activate a block or button
	case 'l':
		piece->changeSensitivity(10);
		buttons->changeSensitivity(10);
		break;
	default:
		break;
	}
}

///////////////////////////////////////////////////////////////
void GameCore::changeState(int aState) {
	switch(aState) {
	case IDLE_STATE:
		cout << "IDLE_STATE" << endl;
		state = IDLE_STATE;
		break;
	case RECO_STATE:
		cout << "RECO_STATE" << endl;;
		state = RECO_STATE;
		break;
	case MOVE_STATE:
		cout << "MOVE_STATE" << endl;	
		moveCounter = 0;
		counter = 4;
		elapsedTimeForDisplayUpdate = ofGetElapsedTimeMillis();
		state = MOVE_STATE;
		break;
	case PLAY_STATE:
		cout << "PLAY_STATE" << endl;
		elapsedTimeForDisplayUpdate = ofGetElapsedTimeMillis();
		state = PLAY_STATE;
		break;
	case OVER_STATE:
		cout << "OVER_STATE" << endl;
		board->reset();
		score->reset();
		state = OVER_STATE;
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
