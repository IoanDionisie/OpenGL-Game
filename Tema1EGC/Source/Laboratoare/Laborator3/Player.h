#pragma once
#include "GameObject.h"
#include "Object2D.h"


class Player : public GameObject {


public:

	Player::Player();

	Player::~Player();


	void Player::lostOneLife();

	void Player::collisionPlayerEnemy(); 

	void Player::collisionPlayerBullet(); 


};
