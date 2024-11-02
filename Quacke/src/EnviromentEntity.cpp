#include "EnviromentEntity.hpp"

EnviromentEntity::EnviromentEntity(const char* shaderName, const char* modelPath,
	const char* name, float m, float friction, mVector3 pos, mVector3 rot)
	:
	Drawable(shaderName, modelPath),
	Rigidbody(name, m, friction, pos, rot)
{
	initRigidbody(getModel());
}

EnviromentEntity::~EnviromentEntity()
{
}

void EnviromentEntity::update(float physicsFixedDeltaTime, float deltaTime)
{
	updateRigidbody();
}

void EnviromentEntity::move(float deltaTime)
{
}
