#ifndef _IDLE_STATE
#define _IDLE_STATE

#include "GameState.h"
#include "ofImage.h"

class IdleState : public GameState {
public:
	IdleState();
	~IdleState();

	void init();
	void cleanup();

	// pushing and popping states causes pausing/resuming.
	void pause();
	void resume();
	
	void handleEvents();
	void update();
	void draw();

private:
	ofImage	imgLogo;
};

#endif
