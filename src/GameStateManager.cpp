#include "GameStateManager.h"

void GameStateManager::handleEvents() {
	if(!states.empty()) {
		states.back()->handleEvents();
	}
}

void GameStateManager::update() {
	if(!states.empty()) {
		states.back()->update();
	}
}

void GameStateManager::draw() {
	if(!states.empty()) {
		states.back()->draw();
	}
}

void GameStateManager::clear() {
	while(!states.empty()) {
		states.back()->cleanup();
		states.pop_back();
	}
}

void GameStateManager::changeState(GameState *state) {
	// cleanup the current state
	if(!states.empty()) {
		states.back()->cleanup();
		states.pop_back();
	}

	// store and init the new state.
	states.push_back(state);
	states.back()->init();
}
 
// pause the current state and go to a new state
void GameStateManager::pushState(GameState *state) {
	if(!states.empty()) {
		states.back()->pause();
	}

	states.push_back(state);
	states.back()->init();
}

// leave current state and go to previous state
void GameStateManager::popState() {
	if(!states.empty()) {
		states.back()->cleanup();
		states.pop_back();
	}

	if(!states.empty()) {
		states.back()->resume();
	}
}
