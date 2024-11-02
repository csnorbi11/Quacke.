#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <bullet/btBulletDynamicsCommon.h>

#include "glm/gtc/matrix_transform.hpp"
#include "Utilities.hpp"

/**
 * Object which is exists in the game world.
 */
class Entity{
	const char* name;

public:
	mVector3 position;
	mVector3 rotation;
	mVector3 direction;
	
public:
	Entity();
	Entity(const char* nam, mVector3 pos=mVector3(0.0), mVector3 rot = mVector3(0.0), mVector3 dir = mVector3(0.0));
	virtual ~Entity();

	virtual void update(float physicsFixedDeltaTime, float deltaTime) = 0;
	virtual void move(float deltaTime) = 0;

	float calculateDistance(const Entity& target);

	inline const char* getName();

protected:
	void calculateDirection();
	mVector3 distanceVector(const Entity& target);

};
#endif // !ENTITY_H
