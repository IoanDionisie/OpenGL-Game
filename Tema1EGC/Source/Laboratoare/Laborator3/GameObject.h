#pragma once
#include <string>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Component/SimpleScene.h"

class GameObject {

public:

	GameObject();
	~GameObject();

	std::string gameStates[2] = { "Playing", "GameOver"};
	
	float colorX, colorY, colorZ;

	float getTranslateX();
	float getTranslateY();
	float getScaleX();
	float getScaleY();
	float getPositionX();
	float getPositionY();
	float getRotationAngle();
	int getNumberOfLives();
	float getMovingSpeed();
	std::string getGameState();

	void setTranslateX(float translateX);
	void setTranslateY(float translateY);
	void setScaleX(float scaleX);
	void setScaleY(float translateY);
	void setPositionX(float positionX);
	void setPositionY(float positionY);
	void setRotationAngle(float rotationAngle);
	void setNumberOfLives(int numberOfLives);
	void setMovingSpeed(float mvSpeed);
	void setColor(std::string clr);
	void setGameState(std::string gameSt);

	
private:


protected:

	float translateX, translateY;
	float scaleX, scaleY;
	float positionX, positionY;
	float rotationAngle;
	float movingSpeed;

	std::string color;
	std::string gameState;
	int numberOfLives;

};

