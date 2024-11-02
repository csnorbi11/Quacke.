#ifndef ENVIROMENTENTITY_H
#define ENVIROMENTENTITY_H

#include "Drawable.hpp"
#include "Rigidbody.hpp"

/**
 * This is entity which purpose is what it's name says.
 */
struct EnviromentEntity : public Drawable, public Rigidbody
{
	EnviromentEntity(const char* shaderName, const char* modelPath, const char* name, float m, float friction,
		mVector3 pos = mVector3(0, 0, 0), mVector3 rot = mVector3(0, 0, 0));
	~EnviromentEntity();

	void update(float physicsFixedDeltaTime, float deltaTime);
	void move(float deltaTime);
};


#endif // !ENVIROMENTENTITY
