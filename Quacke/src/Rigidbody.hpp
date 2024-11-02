#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <iostream>
#include <bullet/btBulletDynamicsCommon.h>

#include "Model.hpp"
#include "Entity.hpp"


/**
 * Rigidbody which are part of the phyiscs simulation.
 */
class Rigidbody : public Entity {
public:
	btScalar mass;
	btCompoundShape* collider;
	btRigidBody* rigidbody;
	btTransform transform;
	btVector3 localInertia;
	

public:
	bool partOfWorld;
	bool isStatic;
	btScalar friction;

	Rigidbody(const char* name, float m, float friction, 
		mVector3 pos = mVector3(0, 0, 0), mVector3 rot = mVector3(0, 0, 0));
	~Rigidbody();

	/**
	 * Init the rigidbody.
	 * 
	 * \param model
	 */
	void initRigidbody(Model model);
	void updateRigidbody();

	inline float getMass();
};

#endif // !RIGIDBODY_H
