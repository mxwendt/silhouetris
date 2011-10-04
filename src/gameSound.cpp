#include "gameSound.h"

///////////////////////////////////////////////////////////////
void GameSound::loadSoundFiles() {
	loadMusic();
	loadSounds();
}

void GameSound::loadMusic()
{
	setDefaultMusicValues();
	musicIdle.loadSound("music-idle.mp3", true); // gets streamed
	musicReco.loadSound("music-reco.mp3", true); // gets streamed
	musicPlay.loadSound("music-play.mp3", true); // gets streamed
}

void GameSound::loadSounds()
{
	setDefaultSoundValues();
	soundClearLine.loadSound("sound-line.wav");
	soundHitBottom.loadSound("sound-hit.wav");
	soundGameOver.loadSound("sound-gameover.wav");
}

void GameSound::setDefaultMusicValues()
{
	musicIdle.setVolume(DEFAULT_IDLE_MUSIC_VOL);
	musicReco.setVolume(DEFAULT_RECO_MUSIC_VOL);
	musicPlay.setVolume(DEFAULT_PLAY_MUSIC_VOL);

	musicIdle.setLoop(true);
	musicReco.setLoop(true);
	musicPlay.setLoop(true);
}

void GameSound::setDefaultSoundValues()
{
	soundClearLine.setMultiPlay(true);
	soundHitBottom.setMultiPlay(true);

	soundClearLine.setVolume(DEFAULT_FINISHED_LINE_VOL);
	soundHitBottom.setVolume(DEFAULT_STONE_HIT_GROUND_VOL);
	soundGameOver.setVolume(DEFAULT_GAME_OVER_VOL);
}

void GameSound::increaseIdleMusicVol(float aVolume){
	if (musicIdle.volume < 1){
		musicIdle.setVolume(musicIdle.volume += aVolume);
	}	
}
void GameSound::increaseRecoMusicVol(float aVolume){
	if (musicReco.volume < 1){
		musicReco.setVolume(musicReco.volume += aVolume);
	}
}
void GameSound::increasePlayMusicVol(float aVolume){
	if (musicPlay.volume < 1){
		musicPlay.setVolume(musicPlay.volume += aVolume);
	}
}
void GameSound::decreaseIdleMusicVol(float aVolume){
	if (musicIdle.volume > 0){
		musicIdle.setVolume(musicIdle.volume -= aVolume);
	}
}
void GameSound::decreaseRecoMusicVol(float aVolume){
	if (musicReco.volume > 0){
		musicReco.setVolume(musicReco.volume -= aVolume);
	}
}
void GameSound::decreasePlayMusicVol(float aVolume){
	if(musicPlay.volume >0){
		musicPlay.setVolume(musicPlay.volume -= aVolume);
	}
}

float GameSound::getIdleMusicVol(){
	return musicIdle.volume;
}

float GameSound::getRecoMusicVol(){
	return musicReco.volume;
}

float GameSound::getPlayMusicVol(){
	return musicPlay.volume;
}

void GameSound::stopPlayingMusic(){
	if(musicIdle.isStreaming) {
		musicIdle.stop();
	}
	if(musicReco.isStreaming) {
		musicReco.stop();
	}
	if(musicPlay.isStreaming) {
		musicPlay.stop();
	}
}

void GameSound::playIdleMusic(){
	musicIdle.setPosition(0.1f); // this is specific for the current idle sound
	musicIdle.play();
}
void GameSound::playRecoMusic(){
	musicReco.play();
}
void GameSound::playPlayMusic(){
	musicPlay.play();
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