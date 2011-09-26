#include "gameSound.h"

const float GameSound::DEFAULT_IDEL_MUSIC_VOL = 1.0f;
const float GameSound::DEAULT_RECO_MUSIC_VOL = 1.0f;
const float GameSound::DEFAULT_GAME_MUSIC_VOL=1.0f;
const float GameSound::DEFAULT_FINISHED_LINE_VOL = 1.0f;
const float GameSound::DEFAULT_STONE_HIT_Ground_VOL = 1.0f;
const float GameSound::DEFAULT_GAME_OVER_VOL = 1.0f;

void GameSound::loadSoundFiles() {
	loadMusic();
	loadSounds();
}

void GameSound::loadMusic()
{
	setDefaultMusicValues();
	musicIdle.loadSound("musicIdle.mp3", true); // gets streamed
	musicReco.loadSound("musicReco.mp3", true); // gets streamed
	musicGame.loadSound("musicGame.mp3", true);	// gets streamed
}

void GameSound::loadSounds()
{
	setDefaultSoundValues();
	soundClearLine.loadSound("line.wav");
	soundHitBottom.loadSound("hit.wav");
	soundGameOver.loadSound("gameover.wav");
}

void GameSound::setDefaultMusicValues()
{
	musicIdle.setVolume(DEFAULT_IDEL_MUSIC_VOL);
	musicReco.setVolume(DEAULT_RECO_MUSIC_VOL);
	musicGame.setVolume(DEFAULT_GAME_MUSIC_VOL);

	musicIdle.setLoop(true);
	musicReco.setLoop(true);
	musicGame.setLoop(true);
}

void GameSound::setDefaultSoundValues()
{
	soundClearLine.setMultiPlay(true);
	soundHitBottom.setMultiPlay(true);

	soundClearLine.setVolume(DEFAULT_FINISHED_LINE_VOL);
	soundHitBottom.setVolume(DEFAULT_STONE_HIT_Ground_VOL);
	soundGameOver.setVolume(DEFAULT_GAME_OVER_VOL);
}

void GameSound::increaseIdleMusicVol(float volume){
	if (musicIdle.volume < 1){
		musicIdle.setVolume(musicIdle.volume += volume);
	}	
}
void GameSound::increaseRecoMusicVol(float volume){
	if (musicReco.volume < 1){
		musicReco.setVolume(musicReco.volume += volume);
	}
}
void GameSound::increaseGameMusicVol(float volume){
	if (musicGame.volume < 1){
		musicGame.setVolume(musicGame.volume += volume);
	}
}
void GameSound::decreaseIdleMusicVol(float volume){
	if (musicIdle.volume > 0){
		musicIdle.setVolume(musicIdle.volume -= volume);
	}
}
void GameSound::decreaseRecoMusicVol(float volume){
	if (musicReco.volume > 0){
		musicReco.setVolume(musicReco.volume -= volume);
	}
}
void GameSound::decreaseGameMusicVol(float volume){
	if(musicGame.volume >0){
		musicGame.setVolume(musicGame.volume -= volume);
	}
}

float GameSound::getIdleMusicVol(){
	return musicIdle.volume;
}

float GameSound::getRecoMusicVol(){
	return musicReco.volume;
}

float GameSound::getGameMusicVol(){
	return musicGame.volume;
}

void GameSound::stopPlayingMusic(){
	if(musicIdle.isStreaming) {
		musicIdle.stop();
	}
	if(musicReco.isStreaming) {
		musicReco.stop();
	}
	if(musicGame.isStreaming) {
		musicGame.stop();
	}
}

void GameSound::playIdleMusic(){
	musicIdle.play();
	musicIdle.setPosition(0.1f); // this is specific for the current idle sound
}
void GameSound::playRecoMusic(){
	musicReco.play();
}
void GameSound::playGameMusic(){
	musicGame.play();
}
void GameSound::playSoundClearLine(){
	soundClearLine.play();
}
void GameSound::playSoundHitBottom(){
	soundHitBottom.play();
}
void GameSound::playSoundGameOver(){
	soundGameOver.play();
}