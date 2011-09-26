#include "IdleState.h"
#include <iostream>


IdleState::IdleState() {
	//
}

IdleState::~IdleState() {
	//
}

void IdleState::init() {
	std::cout << "IdleState initialized" << std::endl;

	imgLogo.loadImage("logo.jpg");
}

void IdleState::cleanup() {
	std::cout << "IdleState cleaned up" << std::endl;
}

void IdleState::pause() {
	std::cout << "IdleState paused" << std::endl;
}

void IdleState::resume() {
	std::cout << "IdleState resumed" << std::endl;
}

void IdleState::handleEvents() {
	std::cout << "IdleState handled events" << std::endl;
}

void IdleState::update() {
	std::cout << "IdleState updated" << std::endl;
}

void IdleState::draw() {
	std::cout << "IdleState drew" << std::endl;

	imgLogo.draw(140, 250);
}
