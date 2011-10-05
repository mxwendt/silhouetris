#ifndef _GAME_SOUND
#define _GAME_SOUND

#include "ofMain.h"

class GameSound {
public:
	///////////////////////////////////////////////////////////////
	void loadSoundFiles();
	void increaseIdleMusicVol(float aVolume);
	void increaseRecoMusicVol(float aVolume);
	void increasePlayMusicVol(float aVolume);

	void decreaseIdleMusicVol(float aVolume);
	void decreaseRecoMusicVol(float aVolume);
	void decreasePlayMusicVol(float aVolume);

	float getIdleMusicVol();
	float getRecoMusicVol();
	float getPlayMusicVol();

	void loadMusic();
	void loadSounds();
	void setDefaultMusicValues();
	void setDefaultSoundValues();

	void stopPlayingMusic();
	void playIdleMusic();
	void playRecoMusic();
	void playPlayMusic();

	void playSoundClearLine();
	void playSoundHitBottom();
	void playSoundGameOver();
	void playSoundBeep();

private:
	///////////////////////////////////////////////////////////////
	static const int DEFAULT_IDLE_MUSIC_VOL = 1;
	static const int DEFAULT_RECO_MUSIC_VOL = 1;
	static const int DEFAULT_PLAY_MUSIC_VOL = 1;
	static const int DEFAULT_FINISHED_LINE_VOL = 1;
	static const int DEFAULT_STONE_HIT_GROUND_VOL = 1;
	static const int DEFAULT_GAME_OVER_VOL = 1;
	static const int DEFAULT_BEEP_VOL = 1;

	ofSoundPlayer soundClearLine;
	ofSoundPlayer soundHitBottom;
	ofSoundPlayer soundGameOver;
	ofSoundPlayer soundBeep;
	ofSoundPlayer musicIdle;
	ofSoundPlayer musicReco;
	ofSoundPlayer musicPlay;
};

#endif