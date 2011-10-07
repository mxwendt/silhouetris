#include "GameCore.h"

///////////////////////////////////////////////////////////////
void GameCore::setup() {
	ofBackground(39, 40, 32);

	piece = new Piece();
	buttons = new MoveButtons();
	board = new Board();
	score = new Score();
	updateTimer = new MilliTimer();
	countTimer = new MilliTimer();
	levelTimer = new MilliTimer();
	kinect = new Kinect(1500, 3000);

	speed = 1000;
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

	delete updateTimer;
	updateTimer = NULL;

	delete countTimer;
	countTimer = NULL;

	delete levelTimer;
	levelTimer = NULL;

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
			counter = 4;
			updateTimer->setAlarm(500);
			countTimer->setAlarm(1000);
			levelTimer->setAlarm(60000);
			changeState(MOVE_STATE);
			break;
		}
		break;
	case MOVE_STATE:
		kinect->updateDepthImage();
		kinect->separateImage();
		piece->update(kinect->getImages());
		buttons->update(kinect->getImages());
		if(updateTimer->alarm() && !piece->isEmpty()) {
			updateTimer->setAlarm(500);
			if(buttons->isMoveRight()) {
				board->isPossibleMove(piece, 1, 0);
			}
			if(buttons->isMoveLeft()) {
				board->isPossibleMove(piece, -1, 0);
			}				
			if(countTimer->alarm()) {
				counter--;
				countTimer->setAlarm(1000);
			}
			if(counter == 0) {
				updateTimer->setAlarm(speed);
				changeState(PLAY_STATE);
				break;
			}
		}
		break;
	case PLAY_STATE:
		kinect->updateDepthImage();
		kinect->separateImage();
		piece->update(kinect->getImages());
		if(updateTimer->alarm() && !piece->isEmpty()) {
			updateTimer->setAlarm(speed);
			if(!board->isPossibleMove(piece, 0, 1)) {
				board->storePiece(piece, score->calcScore(piece));
				score->update(board->deleteLines());
				if(board->isGameOver()) {
					changeState(OVER_STATE);
					break;
				}
				board->insertNewPiece();
				if(levelTimer->alarm()) {
					levelTimer->setAlarm(60000);
					speed -= speedIncreaseLevel;
				}
				updateTimer->setAlarm(500);
				countTimer->setAlarm(1000);
				counter = 4;
				changeState(MOVE_STATE);
				break;
			}
		}
		break;
	case OVER_STATE:
		kinect->updateDepthImage();
		kinect->separateImage();
		piece->update(kinect->getImages());
		if(piece->isInitialForm()) {
			board->reset();
			score->reset();
			counter = 4;
			updateTimer->setAlarm(500);
			countTimer->setAlarm(1000);
			levelTimer->setAlarm(60000);
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
		// TODO: draw instructions
		break;
	case MOVE_STATE:
		images.drawPlayState();
		kinect->drawBlockImages();
		kinect->drawButtonImages();
		buttons->drawMoveButtons(569, 24);
		images.drawOutline(true);
		board->draw(piece); // < change maybe?
		score->draw(509, 695);
		score->drawCounter(600, 90, counter);
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
		counter = 4;
		updateTimer->setAlarm(500);
		countTimer->setAlarm(1000);
		levelTimer->setAlarm(60000);
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
		counter = 4;
		updateTimer->setAlarm(500);
		countTimer->setAlarm(1000);
		levelTimer->setAlarm(60000);
		changeState(MOVE_STATE);
		break;
	case '4':  
		changeState(PLAY_STATE);
		break;
	case '5':  
		changeState(OVER_STATE);
		break;
	case 'n':
		// increase threshold to the front
		kinect->changeThreshold(50, 0);	
		break;	
	case 'm':
		// decrease threshold to the front
		kinect->changeThreshold(-50, 0);
		break;
	case ',':
		// increase threshold to the back
		kinect->changeThreshold(0, 50);
		break;
	case '.':
		// decrease threshold to the back
		kinect->changeThreshold(0, -50);
		break;
	case 'q':
		// decrease time in sec which it takes to the next level
		timeToLevelUp -= 10;
		break;	
	case 'w':
		// increase time in sec which it takes to the next level
		timeToLevelUp += 10;
		break;
	case 'e':	
		// decrease amount of speed when it levels up
		speedIncreaseLevel -= 10;
		break;	
	case 'r':
		// increase amount of speed when it levels up
		speedIncreaseLevel += 10;
		break;
	case 'o':	
		// decrease speed
		speed -= 100;
		break;	
	case 'i':
		// increase speed
		speed += 100;
		break;
	case 'k':
		// decrease tracking sensibility
		piece->changeSensitivity(-50);
		buttons->changeSensitivity(-50);
		break;
	case 'l':
		// increase tracking sensibility
		piece->changeSensitivity(50);
		buttons->changeSensitivity(50);
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
		cout << "RECO_STATE" << endl;
		state = RECO_STATE;
		break;
	case MOVE_STATE:
		cout << "MOVE_STATE" << endl;
		state = MOVE_STATE;
		break;
	case PLAY_STATE:
		cout << "PLAY_STATE" << endl;
		state = PLAY_STATE;
		break;
	case OVER_STATE:
		cout << "OVER_STATE" << endl;
		state = OVER_STATE;
		break;
	default:
		break;
	}
}
