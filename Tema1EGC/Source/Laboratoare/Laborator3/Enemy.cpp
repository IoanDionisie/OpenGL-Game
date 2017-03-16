#include <iostream>
#include <stdlib.h>     
#include <time.h>  
#include <string>
#include "Enemy.h"


	Enemy::Enemy() {
		setNumberOfLives(rand() % 2 + 1); 
		setMovingSpeed(rand() % 200 + 75);
	}

	Enemy::~Enemy() {

	}

	// If the enemy that has 2 lives is being hit once, his color turns to red and the 
	// scale diminishes.
	void Enemy::lostOneLife() {
		setNumberOfLives(getNumberOfLives() - 1);
		scaleX /= 2;		
		scaleY /= 2;
		setMovingSpeed(getMovingSpeed() * 2);
	}

	// If the enemy has 1 life and takes one shot, it is destroyed
	void Enemy::CollisionEnemyBullet() {
		if (getNumberOfLives() == 1) {
			setNumberOfLives(0);
		} else if (getNumberOfLives() == 2) {
			lostOneLife();
		}
	}

