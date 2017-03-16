#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"


class Laborator3 : public SimpleScene
{
	public:
		Laborator3();
		~Laborator3();

		Player player;
		Enemy enemy;
		GameObject oneLife;
		Enemy boss;
		Bullet enemyBullet;

		std::vector<int> screenColor;
		std::vector<GameObject> life;

		void Init() override;

		float currentMouseX, currentMouseY;

		std::vector<Bullet> bullets;
		std::vector<Bullet> enemyBullets;
		std::vector<Enemy> enemies;
		

		int bulletCounter;
		int numberOfBullets;
		float windowRadius;
		float resX, resY;
		float dirX, dirY, hyp;
		float lastTime;
		float timeBehind; 
		float targetTimeStep;

		int wonGame;

		float timeBehindBullet;
		float lastTimeBullet;
		float targetTimeStepBullet ;

		float scaleAnimationTime;
		float gameOverAnimation;

		int killedEnemies;
		bool bossKilled;
		float windowX, windowY;

		float enemyX, enemyY;


	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		glm::mat3 modelMatrix;
		glm::mat3 modelMatrix2;
		float translateX, translateY;
		float scaleX, scaleY;
		float angularStep;
};
