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
	kinect = new Kinect(500, 1500);

	moveLeftActive = false;
	moveRightActive = false;

	// defaults
	movePeriod = 6;
	speed = 1000;

	/*score->loadScore();*/

	board->setInitialBlocks(1);

	changeState(IDLE_STATE);
}

void GameCore::exit() {
	/*score->saveScore();*/

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
			counter = movePeriod;
			updateTimer->setAlarm(500);
			countTimer->setAlarm(1000);
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
				if(board->isPossibleMove(piece, 1, 0)) {
					moveRightActive = true;
				}
			}
			else if(buttons->isMoveLeft()) {
				if(board->isPossibleMove(piece, -1, 0)) {
					moveLeftActive = true;
				}
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
					board->reset();
					board->centerPiece();
					changeState(OVER_STATE);
					break;
				}
				board->insertNewPiece();
				updateTimer->setAlarm(500);
				countTimer->setAlarm(1000);
				counter = movePeriod;
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
			counter = movePeriod;
			updateTimer->setAlarm(500);
			countTimer->setAlarm(1000);
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
		board->drawInitialBlocks();
		board->draw(piece);
		board->drawBottomRow();
		score->draw(520, 690);
		break;
	case MOVE_STATE:
		images.drawMoveState();
		kinect->drawBlockImages();
		kinect->drawButtonImages();
		if(moveRightActive) {
			moveRightActive = false;
			buttons->drawMoveButtonRight(569, 24);
		}
		else if(moveLeftActive) {
			moveLeftActive = false;
			buttons->drawMoveButtonLeft(569, 24);
		}
		images.drawOutline(true);
		board->drawPieceColumn();
		board->draw(piece);
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
		board->drawInitialBlocks();
		board->draw(piece);
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
		// go straight to game over state
		score->updateScore();
		board->reset();
		board->centerPiece();
		changeState(OVER_STATE);
		break;
	case ' ':
		// go straight to move left and right state
		score->reset();
		board->reset();
		board->centerPiece();
		counter = movePeriod;
		updateTimer->setAlarm(500);
		countTimer->setAlarm(1000);
		moveRightActive = false;
		moveLeftActive = false;
		changeState(MOVE_STATE);
		break;
	case OF_KEY_DOWN:
		// go straight to idle state
		score->reset();
		board->reset();
		board->centerPiece();
		counter = movePeriod;
		updateTimer->setAlarm(500);
		countTimer->setAlarm(1000);
		changeState(IDLE_STATE);
		break;
	///////////////////////////////////////////////////////////////
	case '1':
		// change start off form
		// OOX
		// XXX
		// OXX
		// OXX
		board->setInitialBlocks(1);
		break;
	case '2':
		// change start off form
		// OXO
		// XXX
		// OXO
		// OXO
		board->setInitialBlocks(2);
		break;
	case '3':
		// change start off form
		// XXX
		// OOX
		// OOX
		// OOX
		board->setInitialBlocks(3);
		break;
	case '4':
		// change start off form
		// OOO
		// OOO
		// XXO
		// XXO
		board->setInitialBlocks(4);
		break;
	///////////////////////////////////////////////////////////////
	case 'n':
		// move the front of the “tracked-area” back by 5 cm
		kinect->changeThreshold(50, 0);	
		break;	
	case 'm':
		// move the front of the “tracked-area” forth by 5 cm
		kinect->changeThreshold(-50, 0);
		break;
	case ',':
		// move the back of the “tracked-area” back by 5 cm
		kinect->changeThreshold(0, 50);
		break;
	case '.':
		// move the back of the “tracked-area” forth by 5 cm
		kinect->changeThreshold(0, -50);
		break;
	case 'k':
		// reduce amount of pixels that need to be tracked to activate a block or a button by 50 pixels
		piece->changeSensitivity(-50);
		buttons->changeSensitivity(-50);
		break;
	case 'l':
		// increase amount of pixels that need to be tracked to activate a block or a button by 50 pixels
		piece->changeSensitivity(50);
		buttons->changeSensitivity(50);
		break;
	///////////////////////////////////////////////////////////////
	case 'z':
		// decrease “time-to-move” by 1 sec (never goes lower than 3 sec)
		movePeriod -= 1;
		if(movePeriod < 3) {
			movePeriod = 3;
		}
		break;
	case 'u':
		// increase “time-to-move” by 1 sec
		movePeriod += 1;
		break;
	case 'o':
		// increase speed by 0.1 sec
		speed -= 100;
		if(speed < 0.1) {
			speed = 0.1;
		}
		break;	
	case 'i':
		// decrease speed by 0.1 sec
		speed += 100;
		break;
	default:
		break;
	}
}

///////////////////////////////////////////////////////////////
void GameCore::changeState(int aState) {
	switch(aState) {
	case IDLE_STATE:
		state = IDLE_STATE;
		break;
	case RECO_STATE:
		state = RECO_STATE;
		break;
	case MOVE_STATE:
		state = MOVE_STATE;
		break;
	case PLAY_STATE:
		state = PLAY_STATE;
		break;
	case OVER_STATE:
		state = OVER_STATE;
		break;
	default:
		break;
	}
}
