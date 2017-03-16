#include "Laborator3.h"

#include <vector>
#include <iostream>
#include <stdio.h>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"
#include "Enemy.h"
#include <stdlib.h>


using namespace std;


Laborator3::Laborator3()
{
}

Laborator3::~Laborator3()
{
}

float myLim , pas, myY;
float time = 0.25;

void Laborator3::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	cameraInput->SetActive(false);
	
	myLim = window->GetResolution().y * 0.9;
	pas = 2;
	
	Mesh *playerTriangle1, *playerTriangle2;
	Mesh *myBullet;
	Mesh *myEnemyTriangle1, *myEnemyTriangle2;
	Mesh *life;
	Mesh *myBoss;
	Mesh *myEnemyBullet;

	windowX = 1280;
	windowY = 720;

	timeBehind = 0;
	lastTime = 0;
	targetTimeStep = 2;
	

	timeBehindBullet = 0;
	lastTimeBullet = 0;
	targetTimeStepBullet = 1.5;

	currentMouseX = 0;
	currentMouseY = 0;
	
	enemyX = 640;
	enemyY = 360;

	//sqrt((resolution.x / 2)^2 + (resolution.y / 2)^2) + 2;
	windowRadius = 734; 
	
	playerTriangle1 = Object2D::CreateTriangle("playerTriangle1", glm::vec3(0, 0, 1), 50, 0, glm::vec3(0.1, 0.6, 0.3), true);
	playerTriangle2 = Object2D::CreateTriangle("playerTriangle2", glm::vec3(0, 0, 1), 50, glm::pi<float>(), glm::vec3(0.1, 0.6, 0.3), true);
	AddMeshToList(playerTriangle1);
	AddMeshToList(playerTriangle2);

	player.setPositionX(resolution.x / 2);
	player.setPositionY(resolution.y / 2);
	player.setScaleX(1);
	player.setScaleY(1);

	myBullet = Object2D::CreateRectangle("myBullet", glm::vec3(0, 0, 0), 4, 8, glm::vec3(0, 1, 1), true);
	AddMeshToList(myBullet);

	myEnemyBullet = Object2D::CreateRectangle("myEnemyBullet", glm::vec3(0, 0, 0), 4, 8, glm::vec3(0, 1, 1), true);
	AddMeshToList(myEnemyBullet);
	
	life = Object2D::CreateRectangle("life", glm::vec3(0, 0, 1), 30, 15, glm::vec3(0, 1, 1), true);
	AddMeshToList(life);

	myEnemyTriangle1 = Object2D::CreateTriangle("myEnemyTriangle1", 
	glm::vec3(enemy.colorX, enemy.colorY, enemy.colorZ), 50, 0, glm::vec3(0, 0, 1), true);
	
	myEnemyTriangle2 = Object2D::CreateTriangle("myEnemyTriangle2", 
	glm::vec3(enemy.colorX, enemy.colorY, enemy.colorZ), 50, glm::pi<float>(), glm::vec3(0, 0, 1), true);

	enemy.setScaleX(1);
	enemy.setScaleY(1);

	AddMeshToList(myEnemyTriangle1);
	AddMeshToList(myEnemyTriangle2);

	myBoss = Object2D::CreateTriangle("myBoss", glm::vec3(0, 0, 1), 200, 0, glm::vec3(0.3, 0.6, 0.8), true);
	boss.setPositionX(window->GetResolution().x * 0.2);
	boss.setPositionY(window->GetResolution().y  * 0.3);
	boss.setRotationAngle(0);
	boss.setNumberOfLives(10);
	boss.setScaleX(1);
	boss.setScaleY(1);
	bossKilled = false;
	killedEnemies = 0;

	myY = boss.getPositionY();

	AddMeshToList(myBoss);

	for (float i = 0; i < 1; i += 0.0001)
		screenColor.push_back(i);

	wonGame = 2;

	gameOverAnimation = 0;

	// red yellow blue (1, 0, 0), (1, 1, 0), (0, 0, 1)
}

void Laborator3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator3::Update(float deltaTimeSeconds)
{
	if (wonGame == 0) {
		gameOverAnimation += deltaTimeSeconds * 0.25;
		glClearColor(gameOverAnimation, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	} else if (wonGame == 1) {
		gameOverAnimation += deltaTimeSeconds * 0.25;
		glClearColor(0, gameOverAnimation, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	int lifeOffset = 0;

	// Render the lives for the player
	for (int i = 0; i < player.getNumberOfLives(); ++i) {
		if (player.getGameState() == player.gameStates[0]) {
			life.push_back(oneLife);
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(life[i].getPositionX(), life[i].getPositionY());
			life[i].setPositionX(window->GetResolution().x * 9 / 10 + lifeOffset);
			life[i].setPositionY(window->GetResolution().y * 9 / 10);
			RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
			lifeOffset += 30;
		}
	}

	float angle;

	if (player.getGameState() != player.gameStates[1]) {
		angle = atan2(-currentMouseY + window->GetResolution().y - player.getPositionY(), currentMouseX - player.getPositionX());
	
		if (angle < 0)
			angle +=  2 * glm::pi<float>();
		player.setRotationAngle(angle);
	}
	modelMatrix = glm::mat3(1);

	modelMatrix *= Transform2D::Translate(player.getPositionX(), player.getPositionY());
	modelMatrix *= Transform2D::Rotate(player.getRotationAngle());

	RenderMesh2D(meshes["playerTriangle1"], shaders["VertexColor"], modelMatrix);
	RenderMesh2D(meshes["playerTriangle2"], shaders["VertexColor"], modelMatrix);
	

	for (int i = 0; i < bullets.size(); ++i) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(bullets[i].getPositionX(), bullets[i].getPositionY());
		modelMatrix *= Transform2D::Rotate(bullets[i].getRotationAngle());
		if (player.getGameState() != player.gameStates[1]) 
			bullets[i].setMovingSpeed(750);
		else 
			bullets[i].setMovingSpeed(0);
		bullets[i].setPositionX(cos(bullets[i].getRotationAngle()) * bullets[i].getMovingSpeed() * deltaTimeSeconds + bullets[i].getPositionX());
		bullets[i].setPositionY(sin(bullets[i].getRotationAngle()) * bullets[i].getMovingSpeed() * deltaTimeSeconds + bullets[i].getPositionY());

		RenderMesh2D(meshes["myBullet"], shaders["VertexColor"], modelMatrix);
	}

	timeBehind += Engine::GetElapsedTime() - lastTime;
	lastTime = Engine::GetElapsedTime();
	
	if (timeBehind >= targetTimeStep && killedEnemies <= 25) {
		float angle =  glm::radians((float)(rand() % 360));
		enemy.setNumberOfLives(rand() % 2 + 1);
		if (targetTimeStep > 0.6) {
			targetTimeStep -= 0.05;
			cout << targetTimeStep << endl;
		}
		if (enemy.getNumberOfLives() == 2) {
			enemy.colorX = 1;
			enemy.colorY = 1;
			enemy.colorZ = 0;
		} else if (enemy.getNumberOfLives() == 1) {
			enemy.colorX = 0;
			enemy.colorY = 0;
			enemy.colorZ = 1;
		}
		enemy.setPositionX(glm::cos(angle) * windowRadius + windowX / 2);
		enemy.setPositionY(glm::sin(angle) * windowRadius + windowY / 2);
		enemies.push_back(enemy);
		timeBehind -= targetTimeStep;
	}

	for (int i = 0; i < enemies.size(); ++i) {

		modelMatrix = glm::mat3(1);
		
		modelMatrix *= Transform2D::Translate(enemies[i].getPositionX(), enemies[i].getPositionY());
		modelMatrix *= Transform2D::Scale(enemies[i].getScaleX(), enemies[i].getScaleY());

		if (enemies[i].getPositionX() == player.getPositionX())
			enemies[i].setRotationAngle(0);

		if (player.getGameState() != player.gameStates[1]) {
			enemies[i].setRotationAngle(atan2(-enemies[i].getPositionY() + player.getPositionY(),
			 -enemies[i].getPositionX() + player.getPositionX()));
		}

		modelMatrix *= Transform2D::Rotate(enemies[i].getRotationAngle());

		if (player.getGameState() != player.gameStates[1]) {
			enemies[i].setPositionX(enemies[i].getPositionX() + 
			deltaTimeSeconds * enemies[i].getMovingSpeed() * cos(enemies[i].getRotationAngle()));
			enemies[i].setPositionY(enemies[i].getPositionY() + 
			deltaTimeSeconds * enemies[i].getMovingSpeed() * sin(enemies[i].getRotationAngle()));
		} 

		RenderMesh2D(meshes["myEnemyTriangle1"], modelMatrix, glm::vec3(enemies[i].colorX, enemies[i].colorY, enemies[i].colorZ));
		RenderMesh2D(meshes["myEnemyTriangle2"], modelMatrix, glm::vec3(enemies[i].colorX, enemies[i].colorY, enemies[i].colorZ));
	}

	// Collisions
	for (int i = 0; i < enemies.size(); ++i) {
		if (sqrt((player.getPositionX() - enemies[i].getPositionX()) * (player.getPositionX() - enemies[i].getPositionX()) + 
			(player.getPositionY() - enemies[i].getPositionY()) * (player.getPositionY() - enemies[i].getPositionY())) <
			enemies[i].getScaleY() * 35 + player.getScaleY() * 35) {
			
			if (player.getNumberOfLives() == 1)
				wonGame = 0;

			player.setNumberOfLives(player.getNumberOfLives() - 1);
			enemies.erase(enemies.begin() + i);
			killedEnemies ++;
		}
	}

	// Collisions
	for (int i = 0; i < enemies.size(); ++i) {
		for (int j = 0; j < bullets.size(); ++j) {
			if (sqrt((bullets[j].getPositionX() - enemies[i].getPositionX()) * (bullets[j].getPositionX() - enemies[i].getPositionX()) +
				(bullets[j].getPositionY() - enemies[i].getPositionY()) * (bullets[j].getPositionY() - enemies[i].getPositionY())) <
				enemies[i].getScaleY() * 40 + bullets[j].getScaleY() * 4) {

				bullets.erase(bullets.begin() + j);
				
				if (enemies[i].getNumberOfLives() == 2 && enemies[i].getScaleX() > 0.5) {
					enemies[i].setNumberOfLives(enemies[i].getNumberOfLives() - 1);
					enemies[i].setScaleX(enemies[i].getScaleX() - deltaTimeSeconds * 25);
					enemies[i].setScaleY(enemies[i].getScaleY() - deltaTimeSeconds * 25);
					enemies[i].setMovingSpeed(enemies[i].getMovingSpeed() * 2);
					enemies[i].colorX = 0;
					enemies[i].colorY = 1;
					enemies[i].colorZ = 1;
				} else if (enemies[i].getNumberOfLives() == 1) {
					enemies.erase(enemies.begin() + i);
					killedEnemies ++;
					break;
				}
			}
		}
	}

	timeBehindBullet += Engine::GetElapsedTime() - lastTimeBullet;
	lastTimeBullet = Engine::GetElapsedTime();

	if (killedEnemies >= 25 &&  bossKilled == false ) {
		modelMatrix = glm::mat3(1);

		modelMatrix *= Transform2D::Translate(boss.getPositionX(), boss.getPositionY());	

		boss.setPositionX(boss.getPositionX());
		boss.setPositionY(myY);
		boss.setRotationAngle(atan2(-boss.getPositionY() + player.getPositionY(),
			-boss.getPositionX() + player.getPositionX()));
		modelMatrix *= Transform2D::Rotate(boss.getRotationAngle());
			
		if (myY > myLim || myY < 50 && bossKilled == false) {
			pas *= -1;
		} 

		if (bossKilled == true || wonGame == false || wonGame == true)
			pas = 0;

		myY += pas;

		if (bossKilled == false)
			RenderMesh2D(meshes["myBoss"], shaders["VertexColor"], modelMatrix);

		if (timeBehindBullet >= targetTimeStepBullet && bossKilled == false) {
			enemyBullet.setPositionX(boss.getPositionX());
			enemyBullet.setPositionY(boss.getPositionY());
			enemyBullet.setScaleX(1);
			enemyBullet.setScaleY(1);
			enemyBullets.push_back(enemyBullet);
			enemyBullets.push_back(enemyBullet);

			timeBehindBullet -= targetTimeStepBullet;
		}

		for (int i = 0; i < enemyBullets.size(); ++i) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(enemyBullets[i].getPositionX(), enemyBullets[i].getPositionY());
			modelMatrix *= Transform2D::Rotate(enemyBullets[i].getRotationAngle());
			if (player.getGameState() != player.gameStates[1] && bossKilled == false)
				enemyBullets[i].setMovingSpeed(750);
			else
				enemyBullets[i].setMovingSpeed(0);

			enemyBullets[i].setPositionX(cos(enemyBullets[i].getRotationAngle()) *  enemyBullets[i].getMovingSpeed() * deltaTimeSeconds + enemyBullets[i].getPositionX());
			enemyBullets[i].setPositionY(sin(enemyBullets[i].getRotationAngle()) *  enemyBullets[i].getMovingSpeed() * deltaTimeSeconds + enemyBullets[i].getPositionY());
		
			if (bossKilled == false)
				RenderMesh2D(meshes["myEnemyBullet"], shaders["VertexColor"], modelMatrix);
		}

		// Collisions
		for (int j = 0; j < bullets.size(); ++j) {
			if (sqrt((bullets[j].getPositionX() - boss.getPositionX()) * (bullets[j].getPositionX() - boss.getPositionX()) +
				(bullets[j].getPositionY() - boss.getPositionY()) * (bullets[j].getPositionY() - boss.getPositionY())) <
				boss.getScaleY() * 100 + bullets[j].getScaleY() * 5) {

				boss.setNumberOfLives(boss.getNumberOfLives() - 1);
				if (boss.getNumberOfLives() == 0) {
					bossKilled = true;
					player.setGameState(player.gameStates[1]);
					wonGame = 1;
				}
				bullets.erase(bullets.begin() + j);
			}
		}

		// Collisions
		for (int j = 0; j < enemyBullets.size(); ++j) {
			if (sqrt((enemyBullets[j].getPositionX() - player.getPositionX()) * (enemyBullets[j].getPositionX() - player.getPositionX()) +
				(enemyBullets[j].getPositionY() - player.getPositionY()) * (enemyBullets[j].getPositionY() - player.getPositionY())) <
				player.getScaleY() * 30 + enemyBullets[j].getScaleY() * 5) {
				
				wonGame = 0;
				enemyBullets.erase(enemyBullets.begin() + j);
				
				player.setGameState(player.gameStates[1]);
			}
		}
	}
	// The game is over
	if (player.getNumberOfLives() == 0) {
		wonGame = 0;
		player.setGameState(player.gameStates[1]);
	} 

	
}

void Laborator3::FrameEnd()
{

}

void Laborator3::OnInputUpdate(float deltaTime, int mods)
{
	if (player.getGameState() != player.gameStates[1]) {
		if (window->KeyHold(GLFW_KEY_W)) {
			player.setPositionY(deltaTime  * player.getMovingSpeed() + player.getPositionY());
		 }

		if (window->KeyHold(GLFW_KEY_S)) {
			player.setPositionY(-deltaTime  * player.getMovingSpeed() + player.getPositionY());
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			player.setPositionX(-deltaTime  * player.getMovingSpeed() + player.getPositionX());
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			player.setPositionX(deltaTime  * player.getMovingSpeed() + player.getPositionX());
		}
	}
}

void Laborator3::OnKeyPress(int key, int mods)
{
	
	// add key press event
	
}

void Laborator3::OnKeyRelease(int key, int mods)
{
	// add key release event

}

void Laborator3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	currentMouseX = mouseX;
	currentMouseY = mouseY;
}

void Laborator3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{	
	Bullet bullet;

	bullet.setPositionX(player.getPositionX());
	bullet.setPositionY(player.getPositionY());
	bullet.setScaleX(1);
	bullet.setScaleY(1);
	bullet.setRotationAngle(player.getRotationAngle());
	bullets.push_back(bullet);
}

void Laborator3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator3::OnWindowResize(int width, int height)
{
}
