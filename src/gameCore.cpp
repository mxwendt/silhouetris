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

	// defaults
	initialSpeed = 1000;
	initialSpeedIncrease = 250;
	initialLevelPeriod = 60000;
	initialCounterPeriod = 4000;

	speed = initialSpeed;

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
		if(piece->isInitialBlocks(board->getInitialBlocks())) {
			counter = initialCounterPeriod / 1000;
			updateTimer->setAlarm(500);
			countTimer->setAlarm(1000);
			levelTimer->setAlarm(initialLevelPeriod);
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
					score->updateScore();
					board->centerPiece();
					board->reset();
					changeState(OVER_STATE);
					break;
				}
				board->insertNewPiece();
				if(levelTimer->alarm()) {
					levelTimer->setAlarm(initialLevelPeriod);
					speed -= initialSpeedIncrease;
				}
				updateTimer->setAlarm(500);
				countTimer->setAlarm(1000);
				counter = initialCounterPeriod / 1000;
				changeState(MOVE_STATE);
				break;
			}
		}
		break;
	case OVER_STATE:
		kinect->updateDepthImage();
		kinect->separateImage();
		piece->update(kinect->getImages());
		if(piece->isInitialBlocks(board->getInitialBlocks())) {
			score->reset();
			counter = initialCounterPeriod / 1000;
			speed = initialSpeed;
			updateTimer->setAlarm(500);
			countTimer->setAlarm(1000);
			levelTimer->setAlarm(initialLevelPeriod);
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
		images.drawRecoInstructions();
		board->draw(piece);
		board->drawInitialBlocks();
		board->drawBottomRow();
		score->draw(520, 690);
		break;
	case MOVE_STATE:
		images.drawMoveState();
		kinect->drawBlockImages();
		kinect->drawButtonImages();
		buttons->drawMoveButtons(569, 24);
		images.drawOutline(true);
		board->drawPieceColumn();
		board->draw(piece); // < change maybe?
		//images.drawGameOverZone();
		score->draw(520, 690);
		images.drawMoveInstructions();
		score->drawCounter(225, 170, counter);
		break;
	case PLAY_STATE:
		images.drawPlayState();
		kinect->drawBlockImages();
		piece->drawOverlay(569, 24, 360, 480);
		images.drawOutline(false);
		images.drawPlayInstructions();
		board->drawPieceColumn();
		board->draw(piece);
		images.drawGameOverZone();
		score->draw(520, 690);
		break;
	case OVER_STATE:
		images.drawOverState();
		kinect->drawBlockImages();
		piece->drawOverlay(569, 24, 360, 480);
		images.drawOutline(false);
		images.drawOverInstructions();
		board->draw(piece);
		board->drawInitialBlocks();
		board->drawBottomRow();
		score->draw(520, 690);
		images.drawHighscore();
		score->drawScoreTable(112, 290);
		break;
	default:
		break;
	}
}

void GameCore::keyPressed(int aKey) {
	switch (aKey) {
	///////////////////////////////////////////////////////////////
	case OF_KEY_RETURN:
		// go straight to over state
		board->reset();
		score->reset();
		counter = initialCounterPeriod / 1000;
		speed = initialSpeed;
		updateTimer->setAlarm(500);
		countTimer->setAlarm(1000);
		levelTimer->setAlarm(initialLevelPeriod);
		changeState(OVER_STATE);
		break;
	case ' ':
		// go straight to move state
		board->reset();
		score->reset();
		counter = initialCounterPeriod / 1000;
		speed = initialSpeed;
		updateTimer->setAlarm(500);
		countTimer->setAlarm(1000);
		levelTimer->setAlarm(initialLevelPeriod);
		changeState(MOVE_STATE);
		break;
	case '1':
		// change start off form
		board->setInitialBlocks(1);
		break;
	case '2':
		// change start off form
		board->setInitialBlocks(2);
		break;
	case '3':
		// change start off form
		board->setInitialBlocks(3);
		break;
	case '4':
		// change start off form
		board->setInitialBlocks(4);
		break;
	///////////////////////////////////////////////////////////////
	case 'n':
		// increase tracking threshold to the front by 5 cm
		kinect->changeThreshold(50, 0);	
		break;	
	case 'm':
		// decrease tracking threshold to the front by 5 cm
		kinect->changeThreshold(-50, 0);
		break;
	case ',':
		// increase tracking threshold to the back by 5 cm
		kinect->changeThreshold(0, 50);
		break;
	case '.':
		// decrease tracking threshold to the back by 5 cm
		kinect->changeThreshold(0, -50);
		break;
	case 'q':
		// decrease level time by 5 sec
		initialLevelPeriod -= 5000;
		break;	
	case 'w':
		// increase level time by 5 sec
		initialLevelPeriod += 5000;
		break;
	case 'e':	
		// decrease speed increase when it levels up by 0.1 sec
		initialSpeedIncrease -= 100;
		break;	
	case 'r':
		// increase speed increase when it levels up by 0.1 sec
		initialSpeedIncrease += 100;
		break;
	case 'o':
		// decrease start off speed by 0.1 sec
		initialSpeed -= 100;
		break;	
	case 'i':
		// increase start off speed by 0.1 sec
		initialSpeed += 100;
		break;
	case 'k':
		// decrease tracking sensibility by 50 pixels
		piece->changeSensitivity(-50);
		buttons->changeSensitivity(-50);
		break;
	case 'l':
		// increase tracking sensibility by 50 pixels
		piece->changeSensitivity(50);
		buttons->changeSensitivity(50);
		break;
	case OF_KEY_F1: 
		changeState(IDLE_STATE);
		break;
	case OF_KEY_F2: 
		changeState(RECO_STATE);
		break;
	case OF_KEY_F3:
		// go straight to move state
		board->reset();
		score->reset();
		counter = initialCounterPeriod / 1000;
		speed = initialSpeed;
		updateTimer->setAlarm(500);
		countTimer->setAlarm(1000);
		levelTimer->setAlarm(initialLevelPeriod);
		changeState(MOVE_STATE);
		break;
	case OF_KEY_F4:  
		changeState(PLAY_STATE);
		break;
	case OF_KEY_F5:  
		// go straight to over state
		board->reset();
		score->reset();
		counter = initialCounterPeriod / 1000;
		speed = initialSpeed;
		updateTimer->setAlarm(500);
		countTimer->setAlarm(1000);
		levelTimer->setAlarm(initialLevelPeriod);
		changeState(OVER_STATE);
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
