#ifndef _GAME_SOUND
#define _GAME_SOUND

#include "ofMain.h"

class GameSound {

public:

	void loadSoundFiles();
	void increaseIdleMusicVol(float volume);
	void increaseRecoMusicVol(float volume);
	void increaseGameMusicVol(float volume);

	void decreaseIdleMusicVol(float volume);
	void decreaseRecoMusicVol(float volume);
	void decreaseGameMusicVol(float volume);

	float getIdleMusicVol();
	float getRecoMusicVol();
	float getGameMusicVol();

	void loadMusic();
	void loadSounds();
	void setDefaultMusicValues();
	void setDefaultSoundValues();

	void stopPlayingMusic();
	void playIdleMusic();
	void playRecoMusic();
	void playGameMusic();

	void playSoundClearLine();
	void playSoundHitBottom();
	void playSoundGameOver();

private:
	ofSoundPlayer soundClearLine;
	ofSoundPlayer soundHitBottom;
	ofSoundPlayer soundGameOver;
	ofSoundPlayer musicIdle;
	ofSoundPlayer musicReco;
	ofSoundPlayer musicGame;

	static const float DEFAULT_IDEL_MUSIC_VOL;
	static const float DEAULT_RECO_MUSIC_VOL;
	static const float DEFAULT_GAME_MUSIC_VOL;
	static const float DEFAULT_FINISHED_LINE_VOL;
	static const float DEFAULT_STONE_HIT_Ground_VOL;
	static const float DEFAULT_GAME_OVER_VOL;
};



#endif