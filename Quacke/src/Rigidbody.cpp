#include "Rigidbody.hpp"
#include "Model.hpp"


Rigidbody::Rigidbody(const char* name, float m, float friction, mVector3 pos, mVector3 rot)
	:
	Entity(name,pos,rot),
	mass(m),
	collider(new btCompoundShape()),
	rigidbody(nullptr),
	transform(),
	localInertia(),
	partOfWorld(false),
	isStatic(false),
	friction(friction)
{
	
}

Rigidbody::~Rigidbody()
{

}

void Rigidbody::initRigidbody(Model model)
{

	collider = model.getCompoundCollider();
	if (mass == 0)
	{
		isStatic = true;
		localInertia = btVector3(0, 0, 0);
	}
	else
	{
		collider->calculateLocalInertia(mass, localInertia);
	}


	transform.setIdentity();
	transform.setOrigin(btVector3(Entity::position.x, Entity::position.y, Entity::position.z));

	btQuaternion quaternion;
	quaternion.setEulerZYX(rotation.z * mUtilities::PI / 180.0f, rotation.y * mUtilities::PI / 180.0f, rotation.x * mUtilities::PI / 180.0f);
	transform.setRotation(quaternion);

	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rigidbodyConstrInfo(mass, motionState, collider, localInertia);

	rigidbody = new btRigidBody(rigidbodyConstrInfo);

	rigidbody->setFriction(friction);
}

void Rigidbody::updateRigidbody()
{
	if (!isStatic)
	{
		rigidbody->setActivationState(1);
		rigidbody->getMotionState()->getWorldTransform(transform);

		position.x = transform.getOrigin().x();
		position.y = transform.getOrigin().y();
		position.z = transform.getOrigin().z();

		transform.getRotation().getEulerZYX(rotation.z, rotation.y, rotation.x);
		rotation = rotation * (180.0f / mUtilities::PI);
		
	}
}

inline float Rigidbody::getMass()
{
	return mass;
}
