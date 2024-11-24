#include "Player.hpp"

Player::Player()
	:
	Character("Player",5.0f,0.5f,10.0f),
	moveInput(0.0, 0.0, 0.0)
{
	initCharacter();
}

Player::~Player()
{
	std::cout;
}
	
void Player::update(float physicsFixedDeltaTime, float deltaTime)
{
	cameraPosition = position;
	cameraPosition.y += mheight;
	calculateDirection();
	calculateFrontAndRight();
	move(physicsFixedDeltaTime);
	Character::update(physicsFixedDeltaTime,deltaTime);
}

void Player::move(float physicsFixedDeltaTime)
{
	velocity = (front * moveInput.z + right * moveInput.x) * moveSpeed* physicsFixedDeltaTime;
}

