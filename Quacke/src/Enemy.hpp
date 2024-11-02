#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>

#include "Drawable.hpp"
#include "Entity.hpp"
#include "CharacterController.hpp"

/**
 * Basicly it's enemy type.
 */
class Enemy : public Drawable, public CharacterController
{

public:
	Enemy(const char* shaderName, const char* modelPath, const char* name,
		float movespeed, float jumpspeed = 8.0f,
		mVector3 pos = mVector3(0,0,0), mVector3 rot = mVector3(0, 0, 0));
	~Enemy();

	void update(float physicsFixedDeltaTime, float deltaTime);
	void update(float deltaTime, const Entity& target);
	void move(float deltaTime);
};

#endif // !ENEMY_H
