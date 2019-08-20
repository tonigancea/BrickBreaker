#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 origin = glm::vec3(0, 0, 0);
	glm::vec3 lightBlue = glm::vec3(0, 0.84, 1);
	glm::vec3 white = glm::vec3(1, 1, 1);
	glm::vec3 red = glm::vec3(1, 0.2, 0.2);
	glm::vec3 green = glm::vec3(0.7, 1, 0.7);

	//walls
	Mesh* wallLeft = Object2D::CreateRectangle("wallLeft", origin, wallThickness, wallHeight, lightBlue, true);
	AddMeshToList(wallLeft);

	Mesh* wallRight = Object2D::CreateRectangle("wallRight", origin, wallThickness, wallHeight, lightBlue, true);
	AddMeshToList(wallRight);

	Mesh* wallTop = Object2D::CreateRectangle("wallTop", origin, wallWidth, wallThickness, lightBlue, true);
	AddMeshToList(wallTop);

	//platform
	Mesh* platform = Object2D::CreateRectangle("platform", origin, platformWidth, platformHeight, lightBlue, true);
	AddMeshToList(platform);

	//ball
	Mesh* ball = Object2D::CreateCircle("ball", origin, ballRadius, white, true);
	AddMeshToList(ball);

	//lives
	Mesh* life = Object2D::CreateCircle("life", origin, ballRadius, red, true);
	AddMeshToList(life);

	//brick
	Mesh* brick = Object2D::CreateRectangle("brick", origin, brickWidth, brickHeight, lightBlue, true);
	AddMeshToList(brick);

	//powerUp
	Mesh* powerUp = Object2D::CreateRectangle("powerUp", origin, powerUpSize, powerUpSize, green, true);
	AddMeshToList(powerUp);

	Mesh* bonusWall = Object2D::CreateRectangle("bonusWall", origin, wallWidth, wallThickness, green, true);
	AddMeshToList(bonusWall);

	ResetBricks();
	ResetPowerUps();
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

}

void Tema1::ResetPowerUps()
{
	powerUpActivated = false;
	powerUpFalling = false;
	pUty = 0;
	timeDx = powerUpTimeLeft;
}

void Tema1::ResetBricks()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			brick_matrix[i][j] = true;
			brick_scale[i][j] = 1;
		}
	}
}

bool Tema1::CheckTopWallColision(float x, float y)
{

	if (y + ballRadius > 720 - wallThickness)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool Tema1::CheckBonusWallColision(float x, float y)
{

	if (y - ballRadius < wallThickness)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool Tema1::CheckLeftWallColision(float x, float y)
{

	if (x - ballRadius < wallThickness)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool Tema1::CheckRightWallColision(float x, float y)
{

	if (x + ballRadius > 1280 - wallThickness)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool Tema1::CheckPlatformCollision(float x, float y)
{
	if (x >= platformX && x <= platformX + platformWidth &&
		y - ballRadius < platformY + platformHeight &&
		y + ballRadius > platformY) {
		return true;
	}
	
	else
	{
		return false;
	}
}

bool Tema1::CheckLostBall(float x, float y)
{
	if (y < 0)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool Tema1::CheckBrickCollisionUp(float BrickX, float BrickY)
{
	for (int i = 0; i < 360; i = i + 10) {
		float x = ballX + ballRadius * (float)cos(i * M_PI / 180);
		float y = ballY + ballRadius * (float)sin(i * M_PI / 180);

		if (x > BrickX && x < BrickX + brickWidth &&
			y > BrickY + brickHeight - brickOffsetInside &&
			y < BrickY + brickHeight)
		{
			return true;
		}
	}
	
	return false;
}

bool Tema1::CheckBrickCollisionDown(float BrickX, float BrickY)
{
	for (int i = 0; i < 360; i = i + 10) {
		float x = ballX + ballRadius * (float)cos(i * M_PI / 180);
		float y = ballY + ballRadius * (float)sin(i * M_PI / 180);

		if (x > BrickX && x < BrickX + brickWidth &&
			y > BrickY &&
			y < BrickY + brickOffsetInside)
		{
			return true;
		}
	}
	
	return false;
}

bool Tema1::CheckBrickCollisionLeft(float BrickX, float BrickY)
{
	for (int i = 0; i < 360; i = i + 10) {
		float x = ballX + ballRadius * (float)cos(i * M_PI / 180);
		float y = ballY + ballRadius * (float)sin(i * M_PI / 180);

		if (x > BrickX &&
			x < BrickX + brickOffsetInside &&
			y > BrickY &&
			y < BrickY + brickHeight)
		{
			return true;
		}
	}

	return false;
}

bool Tema1::CheckBrickCollisionRight(float BrickX, float BrickY)
{
	for (int i = 0; i < 360; i = i + 10) {
		float x = ballX + ballRadius * (float)cos(i * M_PI / 180);
		float y = ballY + ballRadius * (float)sin(i * M_PI / 180);

		if (x > BrickX + brickWidth - brickOffsetInside &&
			x < BrickX + brickWidth &&
			y > BrickY &&
			y < BrickY + brickHeight)
		{
			return true;
		}
	}
	
	return false;
}

float Tema1::ReflectUp(float oldTy)
{
	float ty = oldTy;
	if (oldTy < 0) {
		ty = -oldTy;
	}
	return ty;
}

float Tema1::ReflectDown(float oldTy)
{
	float ty = oldTy;
	if (oldTy > 0) {
		ty = -oldTy;
	}
	return ty;
}

float Tema1::ReflectLeft(float oldPseudoAngle)
{
	float pseudoAngle = oldPseudoAngle;
	if (oldPseudoAngle > 0) {
		pseudoAngle = -oldPseudoAngle;
	}

	if (ballX + ballRadius > 1280 - wallThickness) {
		ballX = 1280 - wallThickness - ballRadius - 1;
	}
	return pseudoAngle;
}

float Tema1::ReflectRight(float oldPseudoAngle)
{
	float pseudoAngle = oldPseudoAngle;
	if (oldPseudoAngle < 0) {
		pseudoAngle = -oldPseudoAngle;
	}

	if (ballX - ballRadius < wallThickness) {
		ballX = wallThickness + ballRadius + 1;
	}
	return pseudoAngle;
}

void Tema1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(0, 120);
	RenderMesh2D(meshes["wallLeft"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(1265, 120);
	RenderMesh2D(meshes["wallRight"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(0, 705);
	RenderMesh2D(meshes["wallTop"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(platformX, platformY);
	RenderMesh2D(meshes["platform"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Scale(10.0f, 10.0f);
	modelMatrix *= Transform2D::Translate(platformX, 300);
	RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);

	if (waitLaunch)
	{
		ballX = platformX + (platformWidth / 2);
		ballY = platformHeight + platformY + ballRadius;
		pseudoAngle = 0;
		ty = ballSpeed;
	}

	else
	{
		tx = pseudoAngle * ballSpeed;

		ballX += tx * deltaTimeSeconds;
		ballY += ty * deltaTimeSeconds;

		if (CheckLeftWallColision(ballX, ballY))
		{
			pseudoAngle = ReflectRight(pseudoAngle);
		}

		else if (CheckRightWallColision(ballX, ballY))
		{
			pseudoAngle = ReflectLeft(pseudoAngle);
		}

		else if (CheckTopWallColision(ballX, ballY))
		{
			ty = ReflectDown(ty);
		}

		else if (CheckBonusWallColision(ballX, ballY) && powerUpActivated)
		{
			ty = ReflectUp(ty);
		}

		else if (CheckPlatformCollision(ballX, ballY))
		{
			ty = ReflectUp(ty);
			pseudoAngle = ((2 / platformWidth) * (ballX - platformX)) - 1;
		}

		else if (CheckLostBall(ballX, ballY))
		{
			waitLaunch = true;
			lives -= 1;
			if (lives == 0) {
				ResetBricks();
				ResetPowerUps();
				lives = 3;
			}
		}
	}

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(ballX, ballY);
	RenderMesh2D(meshes["ball"], shaders["VertexColor"], modelMatrix);

	for (int l = 0; l < lives; l++)
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(30 + (((float)l)*30), 30);
		RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (brick_scale[i][j] > 0.1)
			{
				float currentBrickX = startX_brick + ((brickWidth + brickOffsetWidth)*j);
				float currentBrickY = startY_brick + ((brickHeight + brickOffsetHeight)*i);

				if (brick_matrix[i][j] == false)	//am avut coliziune
				{
					brick_scale[i][j] -= scaleFactor * deltaTimeSeconds;
					if (powerUpI == i && powerUpJ == j)
					{
						powerUpFalling = true;

						powerUpX = currentBrickX + (brickWidth / 2);
						powerUpY = currentBrickY + (brickHeight / 2);
					}
				}


				modelMatrix = glm::mat3(1);
				//aici am tinut cont si de offsetul adaugat (acea dimensiune/2) pentru a face ca scalarea sa fie centrata
				modelMatrix *= Transform2D::Translate(currentBrickX + (brickWidth / 2), currentBrickY + (brickHeight / 2));
				modelMatrix *= Transform2D::Scale(brick_scale[i][j], brick_scale[i][j]);
				modelMatrix *= Transform2D::Translate(-(brickWidth / 2), -(brickHeight / 2));
				RenderMesh2D(meshes["brick"], shaders["VertexColor"], modelMatrix);
			}
			
		}
	}

	if (powerUpFalling)
	{
		
		pUty += deltaTimeSeconds;
		powerUpAngle += deltaTimeSeconds * powerUpRotateSpeed;
		if (powerUpAngle > 360) {
			powerUpAngle = 0;
		}
		powerUpY -= pUty;

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(powerUpX, powerUpY);
		modelMatrix *= Transform2D::Rotate((float)(powerUpAngle * M_PI / 180));
		modelMatrix *= Transform2D::Translate(-(powerUpSize / 2), -(powerUpSize / 2));
		RenderMesh2D(meshes["powerUp"], shaders["VertexColor"], modelMatrix);
	}

	if (CheckPlatformCollision(powerUpX, powerUpY))
	{
		powerUpActivated = true;
	}

	if (powerUpActivated)
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(0, 0);
		RenderMesh2D(meshes["bonusWall"], shaders["VertexColor"], modelMatrix);

		timeDx -= deltaTimeSeconds;
		printf("%f", timeDx);
	}

	if (timeDx < 0)
	{
		powerUpActivated = false;
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (brick_matrix[i][j])		// nu vreau coliziune cand brick-ul a inceput sa se micsoreze
			{
				float currentBrickX = startX_brick + ((brickWidth + brickOffsetWidth)*j);
				float currentBrickY = startY_brick + ((brickHeight + brickOffsetHeight)*i);

				if (CheckBrickCollisionUp(currentBrickX, currentBrickY))
				{
					ty = ReflectUp(ty);
					brick_matrix[i][j] = false;
				}

				if (CheckBrickCollisionDown(currentBrickX, currentBrickY))
				{
					ty = ReflectDown(ty);
					brick_matrix[i][j] = false;
				}

				if (CheckBrickCollisionLeft(currentBrickX, currentBrickY))
				{
					pseudoAngle = ReflectLeft(pseudoAngle);
					brick_matrix[i][j] = false;
				}

				if (CheckBrickCollisionRight(currentBrickX, currentBrickY)) {
					pseudoAngle = ReflectRight(pseudoAngle);
					brick_matrix[i][j] = false;
				}
			}
		}
	}
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	platformX = (float)mouseX - (platformWidth / 2);
	platformY = (float)15;
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
	if (button == 1) {
		waitLaunch = false;
	}
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
