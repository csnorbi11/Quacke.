#ifndef PLAYER_H
#define PLAYER_H


#include "Entity.hpp"
#include "CharacterController.hpp"


/**
 * The player.
 */
struct Player : public CharacterController
{

	mVector3 moveInput;
	mVector3 cameraPosition;

	Player();
	~Player();

	void update(float deltaTime);
	//calculates the velocity by the inputs
	void move(float deltaTime);
};

#endif // !Player
