#ifndef _GAME_STATE
#define _GAME_STATE

class GameState {
public:
	virtual void init() = 0;
	virtual void cleanup() = 0;

	// pushing and popping states causes pausing/resuming.
	virtual void pause() = 0;
	virtual void resume() = 0;
	
	virtual void handleEvents() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
};

#endif
