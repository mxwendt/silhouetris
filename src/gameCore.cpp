#include "gameCore.h"

void GameCore::setup() {

	gameSound.loadSoundFiles();

	gameLogic.init();
	userImput.init();
	graficEngine.init();

	loadExternalData();
	
	// set values
	isIdleMode = true;
	isRecoMode = false;
	isGameMode = false;
	isOverMode = false;
	clearScreen = false;
	moveLeft = false;
	moveRight = false;
	highscore = 0;
	pieceY = 0;
	pieceX = 3;
	nearThreshold = 1500;
	farThreshold = 3000;
	timeToLevelUp = 60;
	blockSpeed = 1000;
	speedIncreaseLevel = 200;

	// clear matrices
	clearPieceBlocks(activeBlocks);
	clearPieceBlocks(pieceBlocks);
	clearGameBlocks(gameBlocks);

	// init kinect
	kinect = new Kinect();
	nearThreshold = 1000;
	farThreshold = 3000;

	// set background color
	ofBackground(39, 40, 32);
}

void GameCore::update() {
	if(isIdleMode) {
		updateDepthStream();
		checkActiveBlocks();
	}
	else if(isRecoMode) {
		updateDepthStream();
		checkActiveBlocks();
	
		pieceY = 0;
		pieceX = 3;
		setPieceBlocks();
	}
	else if(isGameMode) {
		updateDepthStream();

		if(ofGetElapsedTimeMillis() - elapsedTimeForDisplayUpdate > blockSpeed) {
			updateGameScreen();
			elapsedTimeForDisplayUpdate = ofGetElapsedTimeMillis();
		}
	}
	else {
		updateDepthStream();
		resetGame();
		checkActiveBlocks();
	}
}

void GameCore::draw() {
	if(isIdleMode) {
		ofSetColor(255, 255, 255);
		imgLogo.draw(140, 250);
		imgCopyright.draw(415, 600);
	}
	else if(isRecoMode) {
		drawBG();
		drawSilhouette(SILHOUETTESCREENX, SILHOUETTESCREENY, SILHOUETTEBLOCKSIZE);
		drawBoard();
		drawPiece();
		drawScore();

		// draw cross that has to be formed by player
		ofSetPolyMode(OF_POLY_WINDING_NONZERO);
		ofNoFill();
		ofSetLineWidth(3);
		ofBeginShape();
			ofVertex(4 * BLOCKSIZE + GAMESCREENX, GAMESCREENY);
			ofVertex(5 * BLOCKSIZE + GAMESCREENX, GAMESCREENY);
			ofVertex(5 * BLOCKSIZE + GAMESCREENX, BLOCKSIZE + GAMESCREENY);
			ofVertex(6 * BLOCKSIZE + GAMESCREENX, BLOCKSIZE + GAMESCREENY);
			ofVertex(6 * BLOCKSIZE + GAMESCREENX, 2 * BLOCKSIZE + GAMESCREENY);
			ofVertex(5 * BLOCKSIZE + GAMESCREENX, 2 * BLOCKSIZE + GAMESCREENY);
			ofVertex(5 * BLOCKSIZE + GAMESCREENX, 4 * BLOCKSIZE + GAMESCREENY);
			ofVertex(4 * BLOCKSIZE + GAMESCREENX, 4 * BLOCKSIZE + GAMESCREENY);
			ofVertex(4 * BLOCKSIZE + GAMESCREENX, 2 * BLOCKSIZE + GAMESCREENY);
			ofVertex(3 * BLOCKSIZE + GAMESCREENX, 2 * BLOCKSIZE + GAMESCREENY);
			ofVertex(3 * BLOCKSIZE + GAMESCREENX, BLOCKSIZE + GAMESCREENY);
			ofVertex(4 * BLOCKSIZE + GAMESCREENX, BLOCKSIZE + GAMESCREENY);
		ofEndShape();
		ofFill();
		ofSetLineWidth(1);

		ofSetColor(255, 255, 255);
		imgRecoLabel.draw(210, 145);
	}
	else if(isGameMode) {
		drawBG();
		drawSilhouette(SILHOUETTESCREENX, SILHOUETTESCREENY, SILHOUETTEBLOCKSIZE);
		drawBoard();
		drawPiece();
		drawGameOverZone();
		drawScore();

		ofSetColor(255, 255, 255);
		imgGameLabel.draw(210, 145);
	}
	else {
		drawBG();
		drawSilhouette(SILHOUETTESCREENX, SILHOUETTESCREENY, SILHOUETTEBLOCKSIZE);
		drawBoard();
		drawGameOverZone();
		drawScore();

		ofSetColor(255, 255, 255);
		imgOverLabel.draw(200, 20);
	}
}

void GameCore::keyPressed(int key) {
	switch (key) {
		case '1': 
			switchMode('idle'); 
			break;
		case '2': 
			switchMode('reco'); 
			break;
		case '3': 
			switchMode('game'); 
			break;
		case '4': 
			switchMode('over'); 
			break;
		/*case '5': 
			deleteLine(18); 
			break;*/
		case '6':
			gameSound.increaseIdleMusicVol(0.1f);
			cout << "IdleMusicVol" <<  gameSound.getIdleMusicVol() << endl;
			break;
		case '5':
			gameSound.decreaseIdleMusicVol(0.1f);
			cout << "IdleMusicVol" <<  gameSound.getIdleMusicVol() << endl;
			break;
		case '8':
			gameSound.increaseRecoMusicVol(0.1f);
			cout << "RecoMusicVol" <<  gameSound.getRecoMusicVol() << endl;
			break;
		case '7':
			gameSound.decreaseRecoMusicVol(0.1f);
			cout << "RecoMusicVol" <<  gameSound.getRecoMusicVol() << endl;
			break;
		case '0':
			gameSound.increaseRecoMusicVol(0.1f);
			cout << "GameMusicVol" <<  gameSound.getGameMusicVol() << endl;
			break;
		case '9':
			gameSound.decreaseGameMusicVol(0.1f);
			cout << "GameMusicVol" <<  gameSound.getGameMusicVol() << endl;
			break;
		case 'b':
			gameSound.stopPlayingMusic();
			break;
		// increase threshold to the front
		case 'n':
			nearThreshold += 50;		
			if (nearThreshold > kinect->getMaxDepth()) {
				nearThreshold = kinect->getMaxDepth();
			}	
			break;	
		// decrease threshold to the front
		case 'm':
			nearThreshold -= 50;
			if (nearThreshold < 0) {
				nearThreshold = 0;
			}
			break;
		// increase threshold to the back
		case ',':
			farThreshold += 50;	
			if (farThreshold > kinect->getMaxDepth()) {
				farThreshold = kinect->getMaxDepth();
			}
			break;
		// decrease threshold to the back
		case '.':	
			farThreshold -= 50;	
			if (farThreshold < 0) {
				farThreshold = 0;
			}
			break;
		// decrease the time in seconds wich it thakte to the next level
		case 'q':	
			timeToLevelUp -= 10;
			cout << timeToLevelUp << " gameSpeedLevelUp+10" << endl;
			break;	
		// increase the time in seconds wich it thakte to the next level
		case 'w':
			timeToLevelUp += 10;
			cout << timeToLevelUp << " gameSpeedLevelUp-10" << endl;
			break;
		//decrease time in miliseconds how big the increas of "blockSpeed" per level is
		case 'e':	
			speedIncreaseLevel -= 10;
			cout << speedIncreaseLevel << " speedIncreaseLevel-10" << endl;
			break;	
		// increase time in miliseconds how big the increas of "blockSpeed" per level is
		case 'r':
			speedIncreaseLevel += 10;
			cout << speedIncreaseLevel << " speedIncreaseLevel+10" << endl;
			break;
		default:
			break;
	}
}

void GameCore::windowResized(int w, int h) {
	//
}

void GameCore::loadExternalData() {
	// load external image files
	imgLogo.loadImage("logo.jpg");
	imgCopyright.loadImage("copyright.jpg");
	imgLeftWall.loadImage("leftWall.jpg");
	imgRightWall.loadImage("rightWall.jpg");
	imgScoreBG.loadImage("scoreBG.jpg");
	imgB1.loadImage("b1.jpg");
	imgB2.loadImage("b2.jpg");
	imgB3.loadImage("b3.jpg");
	imgB4.loadImage("b4.jpg");
	imgB5.loadImage("b5.jpg");
	imgB6.loadImage("b6.jpg");
	imgRecoLabel.loadImage("recoLabel.jpg");
	imgGameLabel.loadImage("gameLabel.jpg");
	imgOverLabel.loadImage("overLabel.jpg");
	imgOutline.loadImage("outline.jpg");

	// load external font files
	font.loadFont("pixelart.ttf", 44);
}

void GameCore::switchMode(int mode) {
	isIdleMode = false;
	isRecoMode = false;
	isGameMode = false;
	isOverMode = false;

	gameSound.stopPlayingMusic();

	switch(mode) {
		case 'idle':
			isIdleMode = true;
			gameSound.playIdleMusic();
			break;
		case 'reco':
			isRecoMode = true;
			gameSound.playRecoMusic();
			break;
		case 'game':
			isGameMode = true;
			resetGame();
			highscore = 0;
			elapsedTimeForDisplayUpdate = ofGetElapsedTimeMillis();
			elapsedTimeForGameSpeed = ofGetElapsedTimef();
			gameSound.playGameMusic();
			break;
		case 'over':
			isOverMode = true;
			gameSound.playSoundGameOver();
			gameSound.playIdleMusic();
			break;
		default: 
			break;
	}
}

void GameCore::clearPieceBlocks(bool blocks[PIECEWIDTH][PIECEHEIGHT]) {	
	for(int i = 0; i < PIECEWIDTH; i++) {
		for(int j = 0; j < PIECEHEIGHT; j++) {
			blocks[i][j] = false;
		}
	}
}

void GameCore::clearGameBlocks(int blocks[GAMESCREENWIDTH][GAMESCREENHEIGHT]) {
	for(int i = 0; i < GAMESCREENWIDTH; i++) {
		for(int j = 0; j < GAMESCREENHEIGHT; j++) {
			blocks[i][j] = 0;
		}
	}
}

void GameCore::updateDepthStream() {

	unsigned char tracking[640 * 480];
	unsigned char block[120 * 120];

	// getting depth pixels from depth generator
	depthMask.setFromPixels(kinect->getDepthPixels(nearThreshold, farThreshold),
				kinect->getWidth(),
				kinect->getHeight(),
				OF_IMAGE_GRAYSCALE);

	depthStream.setFromPixels(depthMask.getPixels(120, 0, 400, 480, tracking),
						      400,
						      480,
						      OF_IMAGE_GRAYSCALE);

	setActiveBlock(depthStream.getPixels( 20,   0, 120, 120, block), 0, 0);
	setActiveBlock(depthStream.getPixels(140,   0, 120, 120, block), 0, 1);
	setActiveBlock(depthStream.getPixels(260,   0, 120, 120, block), 0, 2);
	setActiveBlock(depthStream.getPixels( 20, 120, 120, 120, block), 1, 0);
	setActiveBlock(depthStream.getPixels(140, 120, 120, 120, block), 1, 1);
	setActiveBlock(depthStream.getPixels(260, 120, 120, 120, block), 1, 2);
	setActiveBlock(depthStream.getPixels( 20, 240, 120, 120, block), 2, 0);
	setActiveBlock(depthStream.getPixels(140, 240, 120, 120, block), 2, 1);
	setActiveBlock(depthStream.getPixels(260, 240, 120, 120, block), 2, 2);
	setActiveBlock(depthStream.getPixels( 20, 360, 120, 120, block), 3, 0);
	setActiveBlock(depthStream.getPixels(140, 360, 120, 120, block), 3, 1);
	setActiveBlock(depthStream.getPixels(260, 360, 120, 120, block), 3, 2);

	setMoveBlock(depthStream.getPixels(  0, 0, 20, 480, block), LEFT);
	setMoveBlock(depthStream.getPixels(380, 0, 20, 480, block), RIGHT);
}

void GameCore::setActiveBlock(unsigned char* pixels, int col, int line) {
	int counter = 0;
	for(int i = 0; i < 120 * 120; i++) {
		if(pixels[i] != 0) {
			counter++;
		}
	}
	if(counter > 1440) {
		activeBlocks[line][col] = true; 
		return;
	} 
	else {
		activeBlocks[line][col] = false;
	}
}

void GameCore::checkActiveBlocks() {
	// check if somebody is in the tracking area
	if(isIdleMode && (activeBlocks[0][0] || activeBlocks[0][1] ||
			  activeBlocks[0][2] || activeBlocks[0][3] ||
			  activeBlocks[1][0] || activeBlocks[1][1] ||
			  activeBlocks[1][2] || activeBlocks[1][3] ||
			  activeBlocks[2][0] || activeBlocks[2][1] ||
			  activeBlocks[2][2] || activeBlocks[2][3])) {
		switchMode('reco');
	}

	// check for cross to start a game
	if(isRecoMode && activeBlocks[1][0] && activeBlocks[0][1] &&
		         activeBlocks[1][1] && activeBlocks[2][1] && 
			 activeBlocks[1][2] && activeBlocks[1][3] &&
			 !activeBlocks[0][0] && !activeBlocks[2][0] &&
			 !activeBlocks[0][2] && !activeBlocks[2][2] &&
			 !activeBlocks[0][3] && !activeBlocks[2][3]) {
		setPieceBlocks();
		switchMode('game');
	}
	
	// check for cross to restart a game
	if(isOverMode && activeBlocks[1][0] && activeBlocks[0][1] &&
			 activeBlocks[1][1] && activeBlocks[2][1] &&
			 activeBlocks[1][2] && activeBlocks[1][3] &&
			 !activeBlocks[0][0] && !activeBlocks[2][0] && 
			 !activeBlocks[0][2] && !activeBlocks[2][2] && 
			 !activeBlocks[0][3] && !activeBlocks[2][3]) {
		setPieceBlocks();
		switchMode('game');
	}

	// check if playerleft trackingarea
	if(isOverMode && (activeBlocks[0][0] || activeBlocks[0][1] ||
			  activeBlocks[0][2] || activeBlocks[0][3] ||
			  activeBlocks[1][0] || activeBlocks[1][1] ||
			  activeBlocks[1][2] || activeBlocks[1][3] || 
			  activeBlocks[2][0] || activeBlocks[2][1] ||
			  activeBlocks[2][2] || activeBlocks[2][3])) {
		switchMode('reco');
	}
}

void GameCore::setPieceBlocks() {
	for(int i1 = pieceX, i2 = 0; i1 < pieceX + PIECEWIDTH; i1++, i2++) {
		for(int j1 = pieceY, j2 = 0; j1 < pieceY + PIECEHEIGHT; j1++, j2++) {
			if(gameBlocks[i1][j1] == 0) {
				pieceBlocks[i2][j2] = activeBlocks[i2][j2];
			}
		}
	}
}

void GameCore::updateGameScreen() {
	// check if somebody is in the tracking area
	if(!activeBlocks[0][0] && !activeBlocks[0][1] &&
	   !activeBlocks[0][2] && !activeBlocks[0][3] &&
	   !activeBlocks[1][0] && !activeBlocks[1][1] &&
	   !activeBlocks[1][2] && !activeBlocks[1][3] &&
	   !activeBlocks[2][0] && !activeBlocks[2][1] &&
	   !activeBlocks[2][2] && !activeBlocks[2][3]) return;

	// safe piece on the board
	setPieceBlocks();
	
	// check if move right or left is possible
	if(!moveRight && moveLeft && isPossibleMove(pieceX - 1, pieceY)) {
		pieceX--;
	}
	if(moveRight && !moveLeft && isPossibleMove(pieceX + 1, pieceY)) {
		pieceX++;
	}
		
	// check if move down is possible
	if(isPossibleMove(pieceX, pieceY + 1)) {
		pieceY++;
	} 
	else {
		storePiece(calcScore());
		if(isGameOver()) {
			switchMode('over');
			return;
		}
		deletePossibleLines();
		insertNewBlockIntoGame();
		checkElapedTime();
	}
}

void GameCore::insertNewBlockIntoGame()
{
	pieceX = 3;
	pieceY = 0;
}

void GameCore::checkElapedTime()
{
	if(ofGetElapsedTimef() - elapsedTimeForGameSpeed >= timeToLevelUp) {
		increaseGamespeed(speedIncreaseLevel);
		elapsedTimeForGameSpeed = ofGetElapsedTimef();

	}
	
	cout << highscore << " highscore" << endl;
	cout << timeToLevelUp << " timeToLevelUp" << endl;
	cout << speedIncreaseLevel << " speedIncreaseLevel" << endl;
	cout << blockSpeed << " blockSpeed" << endl;
}

void GameCore::increaseGamespeed(int miliseconds){
	blockSpeed -= miliseconds;
}

void GameCore::resetGame() {
	clearPieceBlocks(pieceBlocks);
	clearGameBlocks(gameBlocks);
	pieceX = 0;
	pieceY = 0;
	blockSpeed = 1000;
}

void GameCore::drawBG() {
	//  draw walls and label
	ofSetColor(255, 255, 255);
	imgLeftWall.draw(159, 0);
	imgRightWall.draw(590, 0);
	imgScoreBG.draw(623, 510);
	
	// draw white background for board
	ofSetColor(255, 255, 255);
	ofRect(190, 0, 400, 720);
}

void GameCore::drawSilhouette(int x, int y, int size) {
	ofSetColor(255, 255, 255);
	imgOutline.draw(x - 57, y - 10);
	depthStream.draw(x - 50, y, size * 3 + 100, size * 4);

	ofEnableAlphaBlending(); // turn on alpha blending
	ofSetColor(186, 205, 54, 80);
	for(int i = 0; i < PIECEWIDTH; i++) {
		for(int j = 0; j < PIECEHEIGHT; j++) {
			if(activeBlocks[i][j]) {
				ofRect(i * size + x, 
				       j * size + y, size, size);
			}
		}
	}

	ofSetColor(255, 0, 0, 80);
	if(moveLeft) {
		ofRect(x - 50, y, 50, size * 4);
	} 
	else if(moveRight) {
		ofRect(x + size * 3, y, 50, size * 4);
	}
	ofDisableAlphaBlending(); // turn it back off, if you don't need it
}

void GameCore::drawBoard() {
	ofSetColor(255, 255, 255);
	for(int i = 0; i < GAMESCREENWIDTH; i++) {
		for(int j = 0; j < GAMESCREENHEIGHT; j++) {
			if(clearScreen) {
				if(gameBlocks[i][j] == 0) {
					ofRect(i * BLOCKSIZE + GAMESCREENX,
					       j * BLOCKSIZE + GAMESCREENY, BLOCKSIZE, BLOCKSIZE);
				}
			}
			if(gameBlocks[i][j] == 1) {
				imgB1.draw(i * BLOCKSIZE + GAMESCREENX, j * BLOCKSIZE + GAMESCREENY);
			} 
			else if(gameBlocks[i][j] == 2) {
				imgB2.draw(i * BLOCKSIZE + GAMESCREENX, j * BLOCKSIZE + GAMESCREENY);
			} 
			else if(gameBlocks[i][j] == 3) {
				imgB3.draw(i * BLOCKSIZE + GAMESCREENX, j * BLOCKSIZE + GAMESCREENY);
			}
			else if(gameBlocks[i][j] == 4) {
				imgB4.draw(i * BLOCKSIZE + GAMESCREENX, j * BLOCKSIZE + GAMESCREENY);
			} 
			else if(gameBlocks[i][j] == 5) {
				imgB5.draw(i * BLOCKSIZE + GAMESCREENX, j * BLOCKSIZE + GAMESCREENY);
			} 
			else if(gameBlocks[i][j] == 6) {
				imgB6.draw(i * BLOCKSIZE + GAMESCREENX, j * BLOCKSIZE + GAMESCREENY);
			}
		}
	}
	clearScreen = false;
}

void GameCore::drawPiece() {
	for(int i = 0; i < PIECEWIDTH; i++) {
		for(int j = 0; j < PIECEHEIGHT; j++) {
			if(pieceBlocks[i][j]) {
				ofSetColor(186, 205, 54);
				ofRect((i + pieceX) * BLOCKSIZE + GAMESCREENX,
				       (j + pieceY) * BLOCKSIZE + GAMESCREENY, BLOCKSIZE, BLOCKSIZE);
			} 
			else {
				ofEnableAlphaBlending(); // turn on alpha blending
				ofSetColor(186, 205, 54, 80);
				ofRect((i + pieceX) * BLOCKSIZE + GAMESCREENX,
				       (j + pieceY) * BLOCKSIZE + GAMESCREENY, BLOCKSIZE, BLOCKSIZE);
				ofDisableAlphaBlending(); // turn it back off, if you don't need it
			}
		}
	}
}

void GameCore::drawGameOverZone() {
	ofEnableAlphaBlending(); // turn on alpha blending
	ofSetColor(186, 205, 54, 80);
	ofRect(190, 0, 400, 160);
	ofDisableAlphaBlending(); // turn it back off, if you don't need it
}

void GameCore::drawScore() {
	ofSetColor(39, 40, 32);
	stringstream ss;
	ss << highscore;
	font.drawString(ss.str(), 690, 655);
}

int GameCore::calcScore() {
	complexCalcR0 = 0; //top row
	complexCalcR1 = 0;
	complexCalcR2 = 0;
	complexCalcR3 = 0; //bottom row

	// counting pices in each row
	for(int i = 0; i < PIECEWIDTH; i++) {
		for(int j = 0; j < PIECEHEIGHT; j++) {
			if(pieceBlocks[i][j]) {
				switch (j) {
					case 0: 
						complexCalcR0++; 
						break;
					case 1: 
						complexCalcR1++;
						break;
					case 2: 
						complexCalcR2++; 
						break;				
					case 3: 
						complexCalcR3++; 
						break;
					default:
						break;
				}
			}
		}
	}

	if(complexCalcR3 != 0) {
		complexCalc = (3 * complexCalcR0 + 
			       2 * complexCalcR1 + 
				   complexCalcR2 + 
				   complexCalcR3) / complexCalcR3;
	
	} 
	else {
		complexCalc = 3 * complexCalcR0 + 
			      2 * complexCalcR1 + 
				  complexCalcR2;
	}
	
	if(complexCalc <=3 ) {
		return 1;

	} 
	else if(complexCalc <= 6) {
		return 2;
	} 
	else if(complexCalc <= 9) {
		return 3;
	} 
	else if(complexCalc <= 11) {
		return 4;
	} 
	else if(complexCalc <= 14) {
		return 5;
	} 
	else {
		return 6;
	}
}

int GameCore::addUpScore(int line) {
	int tempScore = 0;
	for(int i = 0; i < GAMESCREENWIDTH; i++) {
		tempScore += (gameBlocks[i][line] * 5);
	}
	return tempScore;
}

bool GameCore::isPossibleMove(int pX, int pY) {
	for(int i1 = pX, i2 = 0; i1 < pX + PIECEWIDTH; i1++, i2++) {
		for(int j1 = pY, j2 = 0; j1 < pY + PIECEHEIGHT; j1++, j2++) {
			// check if the piece is outside the limits of the board
			if(i1 < 0 || i1 > GAMESCREENWIDTH - 1 || j1 > GAMESCREENHEIGHT - 1) {	
				if(pieceBlocks[i2][j2]) {
					return false;
				}
			}

			// check for collision with other blocks
			if (j1 >= 0) {
				if(pieceBlocks[i2][j2] && gameBlocks[i1][j1] > 0)
					return false;
			}
		}
	}

	// no collision
	return true;
}

bool GameCore::isGameOver() {
	// if the first line has blocks then the game is over
	for(int i = 0; i < GAMESCREENWIDTH; i++) {
		if(gameBlocks[i][3] > 0) {
			return true;
		}
	}
	return false;
}

void GameCore::setMoveBlock(unsigned char* pixels, int direction) {
	int counter = 0;
	for(int i = 0; i < 20 * 480; i++) {	
		if (pixels[i] != 0) {
			counter++;
		}
	}
	if(counter > 300) {
		if(direction == LEFT) {
			moveLeft = true;
		}
		if(direction == RIGHT) {
			moveRight = true;
		}
		return;
	} 
	else {	
		if(direction == LEFT) {
			moveLeft = false;
		}
		if(direction == RIGHT) {
			moveRight = false;
		}
	}
}

void GameCore::deleteLine (int pY) {
	// moves all the upper lines, except the first 4 startrows, one row down
	for(int j = pY; j > 3; j--) {
		for(int i = 0; i < GAMESCREENWIDTH; i++) {
			gameBlocks[i][j] = gameBlocks[i][j-1];
		}
	}
	gameSound.playSoundClearLine();
}

void GameCore::deletePossibleLines () {
	for(int j = 0; j < GAMESCREENHEIGHT; j++) {
		int i = 0;
		while(i < GAMESCREENWIDTH) {
			if (gameBlocks[i][j] == 0) {
				break;
			}
			i++;
		}
		if(i == GAMESCREENWIDTH) {
			clearScreen = true;			
			highscore += addUpScore(j);	
			deleteLine (j);
		}
	}
	
	/* altes erh�hen von game speed
	if((int)highscore / 300 > gameSpeed) {
		gameSpeed++;
		blockSpeed -= 100;
	}
	*/
}

void GameCore::storePiece(int scoreOfStone) {
	for(int i1 = pieceX, i2 = 0; i1 < pieceX + PIECEWIDTH; i1++, i2++) {
		for(int j1 = pieceY, j2 = 0; j1 < pieceY + PIECEHEIGHT; j1++, j2++) {
			if(pieceBlocks[i2][j2]) {
				gameBlocks[i1][j1] = scoreOfStone;
			}
		}
	}
	gameSound.playSoundHitBottom();
}


