#pragma once
#include "GameObject.h"

class Enemy : public GameObject {

public:

	Enemy::Enemy(); 

	Enemy::~Enemy();

	// If the enemy that has 2 lives is being hit once, his color turns to red and the 
	// scale diminishes.
	void Enemy::lostOneLife();

	// If the enemy has 1 life and takes one shot, it is destroyed
	void Enemy::CollisionEnemyBullet();

};