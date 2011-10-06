#include "GameCore.h"

///////////////////////////////////////////////////////////////
void GameCore::setup() {
	ofBackground(39, 40, 32);

	// init empty piece
	piece = new Piece();

	// init move buttons
	buttons = new MoveButtons();
	
	// init empty board
	board = new Board();

	// init empty score and score table
	score = new Score();

	// init kinect
	kinect = new Kinect(1500, 3000);

	// start off w/ idle state
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
		// update blocks
		kinect->updateDepthImage();
		kinect->separateImage();
		piece->update(kinect->getImages());
		
		// check for user
		if(!piece->isEmpty()) {
			changeState(RECO_STATE);
			break;
		}
		break;
	case RECO_STATE:
		// update blocks
		kinect->updateDepthImage();
		kinect->separateImage();
		piece->update(kinect->getImages());
		
		// check for initial form
		if(piece->isInitialForm()) {
			changeState(MOVE_STATE);
			break;
		}
		break;
	case MOVE_STATE:
		// update blocks
		kinect->updateDepthImage();
		kinect->separateImage();
		buttons->update(kinect->getImages());

		// wait 0.5 seconds
		if(ofGetElapsedTimeMillis() - elapsedTimeForDisplayUpdate > 500) {
			// check for user
			if(!piece->isEmpty()) {
				// move right
				if(buttons->isMoveRight()) {
					board->isPossibleMove(piece, 1, 0);
				}
				// move left
				if(buttons->isMoveLeft()) {
					board->isPossibleMove(piece, -1, 0);
				}

				// get current elapsed time
				elapsedTimeForDisplayUpdate = ofGetElapsedTimeMillis();
				
				moveCounter++;
				
				// update countdown
				if(moveCounter % 2 == 0) {
					counter--;
				}

				// check if time to move is over
				if(moveCounter > 9) {
					changeState(PLAY_STATE);
					break;
				}
			}
		}
		break;
	case PLAY_STATE:
		// update blocks
		kinect->updateDepthImage();
		kinect->separateImage();
		piece->update(kinect->getImages());

		// wait according to blockspeed (default: 1 second)
		if(ofGetElapsedTimeMillis() - elapsedTimeForDisplayUpdate >= blockSpeed) {
			// check for user
			if(!piece->isEmpty()) {
				// check that it can't move down anymore
				if(!board->isPossibleMove(piece, 0, 1)) {
					board->storePiece(piece, score->calcScore(piece));
					score->update(board->deleteLines());

					// check if game is over
					if(board->isGameOver()) {
						changeState(OVER_STATE);
						break;
					}

					board->insertNewPiece();
					checkElapsedTime();
					changeState(MOVE_STATE);
				}
				// get current elapsed time
				elapsedTimeForDisplayUpdate = ofGetElapsedTimeMillis();
			}
		}
		break;
	case OVER_STATE:
		// update blocks
		kinect->updateDepthImage();
		kinect->separateImage();
		piece->update(kinect->getImages());

		// check for initial form
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
		// draw background
		images.drawIdleState();
		break;
	case RECO_STATE:
		// draw background
		images.drawRecoState();
		images.drawOutline(false);

		// draw depth stream
		kinect->drawBlockImages();

		// draw active blocks
		piece->drawOverlay(569, 24, 360, 480);
		
		// draw active piece
		board->draw(piece);

		// draw current score
		score->draw(509, 695);

		// draw instructions

		break;
	case MOVE_STATE:
		// draw background
		images.drawPlayState();
		images.drawOutline(true);

		// draw depth stream
		kinect->drawBlockImages();
		kinect->drawButtonImages();

		// draw active buttons
		buttons->drawMoveButtons(569, 24);
		
		// draw active piece < change maybe?
		board->draw(piece);

		// draw current score
		score->draw(509, 695);

		// draw countdown
		score->drawCounter(600, 90, counter);
		break;
	case PLAY_STATE:
		// draw background
		images.drawPlayState();
		images.drawOutline(false);

		// draw depth stream
		kinect->drawBlockImages();

		// draw active blocks
		piece->drawOverlay(569, 24, 360, 480);
		
		// draw active piece
		board->draw(piece);

		// draw current score
		score->draw(509, 695);
		break;
	case OVER_STATE:
		// draw background
		images.drawOverState();
		images.drawOutline(false);

		// draw depth stream
		kinect->drawBlockImages();

		// draw active blocks
		piece->drawOverlay(569, 24, 360, 480);
		
		// draw active piece
		board->draw(piece);

		// draw current score and score table
		score->draw(509, 695);
		score->drawScoreTable(50, 50);
		break;
	default:
		break;
	}
}

void GameCore::keyPressed(int aKey) {
	switch (aKey) {
	case OF_KEY_RETURN:
		board->reset();
		score->reset();
		//elapsedTimeForDisplayUpdate = ofGetElapsedTimeMillis();
		changeState(MOVE_STATE);
		break;
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
		// set initial values
		blockSpeed = 1000;
		timeToLevelUp = 60;
		speedIncreaseLevel = 200;
		moveCounter = 0;
		counter = 4;
		elapsedTimeForDisplayUpdate = ofGetElapsedTimeMillis();

		// set new state
		cout << "IDLE_STATE" << endl;
		state = IDLE_STATE;
		break;
	case RECO_STATE:
		// set new state
		cout << "RECO_STATE" << endl;
		state = RECO_STATE;
		break;
	case MOVE_STATE:
		// reset counters
		moveCounter = 0;
		counter = 4;

		// get current elapsed time
		//elapsedTimeForDisplayUpdate = ofGetElapsedTimeMillis();

		// set new state
		cout << "MOVE_STATE" << endl;
		state = MOVE_STATE;
		break;
	case PLAY_STATE:
		// get current elapsed time
		//elapsedTimeForDisplayUpdate = ofGetElapsedTimeMillis();

		// set new state
		cout << "PLAY_STATE" << endl;
		state = PLAY_STATE;
		break;
	case OVER_STATE:
		// reset score and board
		board->reset();
		score->reset();

		// set new state
		cout << "OVER_STATE" << endl;
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
