#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();

		void Init() override;

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

		bool CheckTopWallColision(float x, float y);
		bool CheckBonusWallColision(float x, float y);
		bool CheckLeftWallColision(float x, float y);
		bool CheckRightWallColision(float x, float y);
		bool CheckPlatformCollision(float x, float y);
		bool CheckLostBall(float x, float y);
		bool CheckBrickCollisionUp(float BrickX, float BrickY);
		bool CheckBrickCollisionDown(float BrickX, float BrickY);
		bool CheckBrickCollisionLeft(float BrickX, float BrickY);
		bool CheckBrickCollisionRight(float BrickX, float BrickY);
		
		float ReflectUp(float oldTy);
		float ReflectDown(float oldTy);
		float ReflectLeft(float oldPseudoAngle);
		float ReflectRight(float oldPseudoAngle);

		void ResetBricks();
		void ResetPowerUps();

	protected:
		glm::mat3 modelMatrix;

		// walls
		float wallHeight = 600;
		float wallWidth = 1280;
		float wallThickness = 15;

		//platform
		float platformWidth = 200;
		float platformHeight = 15;
		float platformX;
		float platformY;

		//ball
		float ballRadius = 10;
		float ballSpeed = 200;
		float ballX;
		float ballY;
		float tx;
		float ty;

		//brick
		float brickWidth = 40;
		float brickHeight = 20;
		
		float brickOffsetWidth = 25;
		float brickOffsetHeight = 15;
		float brickOffsetInside = 5;

		float startX_brick = (1280 - (12 * brickWidth + 11 * brickOffsetWidth)) / 2;
		float startY_brick = (720 - (10 * brickHeight + 11 * brickOffsetHeight)) / 3 * 2;

		bool brick_matrix[10][12];
		float brick_scale[10][12];
		float scaleFactor = 2;

		//power ups
		float powerUpX;
		float powerUpY;
		float pUty;
		float powerUpI = rand() % 10;
		float powerUpJ = rand() % 12;

		float powerUpSize = 15;
		float powerUpAngle;
		float powerUpRotateSpeed = 100;

		float powerUpTimeLeft = 10;
		float timeDx;
		bool powerUpFalling;
		bool powerUpActivated;


		//gameplay
		bool waitLaunch = true;
		float pseudoAngle;	// not degres or radians
		int lives = 3;
};
