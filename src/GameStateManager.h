#ifndef _GAME_STATE_MANAGER
#define _GAME_STATE_MANAGER

#include <vector>
#include "GameState.h"

class GameStateManager {
public:
	void handleEvents();
	void update();
	void draw();

	void changeState(GameState* state);
	void pushState(GameState* state);
	void popState();
	void clear();
private:
	std::vector<GameState*> states;
};

#endif
