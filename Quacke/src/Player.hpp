#ifndef PLAYER_H
#define PLAYER_H


#include "Entity.hpp"
#include "Character.hpp"


/**
 * The player.
 */
struct Player : public Character
{

	mVector3 moveInput;
	

	Player();
	~Player();

	void update(float physicsFixedDeltaTime, float deltaTime);
	//calculates the velocity by the inputs
	void move(float physicsFixedDeltaTime);

};

#endif // !Player
