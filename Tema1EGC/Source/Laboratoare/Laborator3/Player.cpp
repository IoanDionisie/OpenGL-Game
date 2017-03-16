#include <iostream>
#include "Player.h"

	Player::Player() {
		setGameState(gameStates[0]);   // Start the game
		setRotationAngle(0);
		setNumberOfLives(3);
		setMovingSpeed(300);
	}

	Player::~Player() {

	}

	void Player::lostOneLife() {
		setNumberOfLives(getNumberOfLives() - 1);
	}

	void Player::collisionPlayerEnemy() {
		if (getNumberOfLives() == 1) {
			setGameState(gameStates[1]);
		} else {
			lostOneLife();
		}	
	}

	void Player::collisionPlayerBullet() {
		if (getNumberOfLives() == 1) {
			setGameState(gameStates[1]);
		}
		else {
			lostOneLife();
		}
	}
