#ifndef DYANMICENTITY_H
#define DYNAMICENTITY_H

#include "Drawable.hpp"
#include "Rigidbody.hpp"


class DyanmicEntity : public Drawable, public Rigidbody
{
	btTriangleMeshShape* collider;

	DyanmicEntity(const char* shaderName, const char* modelPath, const char* name, float m, float friction,
		mVector3 pos = mVector3(0, 0, 0), mVector3 rot = mVector3(0, 0, 0));
	~DyanmicEntity();

	void update(float deltaTime);
	void move(float deltaTime);
};


#endif // !ENVIROMENTENTITY
