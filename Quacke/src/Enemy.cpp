#include "Enemy.hpp"


Enemy::Enemy(const char* shaderName, const char* modelPath, const char* name, float movespeed, float jumpspeed,
	mVector3 pos, mVector3 rot)
	:
	Drawable(shaderName, modelPath),
	Character(name, 0, 0, movespeed, jumpspeed, pos, rot)
{
	initCharacter(getModel());
}

Enemy::~Enemy()
{
	
}

void Enemy::update(float physicsFixedDeltaTime, float deltaTime)
{
	Character::update(physicsFixedDeltaTime, deltaTime);
}

void Enemy::update(float deltaTime, const Entity& target)
{
	//calculateDirection();
	//float tmpangle = 0;
	//float distanceLength = glm::length(glm::vec3(distanceVector(target).x, 0, distanceVector(target).z));
	//mVector3 distVec = distanceVector(target);
	//distVec.y = 0;
	//glm::vec3 disVec(distVec.x, distVec.y, distVec.z);
	//float dotProd = glm::dot(glm::vec3(0,0,1), disVec);
	//float angle = glm::acos(dotProd / distanceLength);
	//if (distVec.x < 0)
	//	rotation.y = -glm::degrees(angle);
	//else
	//	rotation.y = glm::degrees(angle);
	////std::cout << "distVec: (" << distVec.x << ":" << distVec.z << ")\t angle:\t" << glm::degrees(angle) << "\t rotation:\t"<<rotation.y << std::endl; ;
	//move(deltaTime, btVector3(0,0,0));
}

void Enemy::move(float deltaTime)
{
	
}
