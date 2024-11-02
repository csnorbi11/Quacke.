#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/BulletDynamics/Character/btKinematicCharacterController.h>
#include <bullet/BulletCollision/CollisionDispatch/btGhostObject.h>

#include "Entity.hpp"
#include "Drawable.hpp"
#include "Model.hpp"

/**
 * Character controller is for "living" entities.
 * (refered as CC later on)
 */
class CharacterController : public Entity {
	
	btTransform transform;

protected:
	mVector3 front;
	mVector3 right;

	float mheight, mwidth;
	float jumpSpeed;

public:
	btKinematicCharacterController* character;
	btPairCachingGhostObject* ghostObject;

	bool isAdded;
	mVector3 velocity;
	float moveSpeed;

public:
	/**
	 * Creates a basic CC with capsule collider.
	 * 
	 */
	CharacterController();
	CharacterController(const char* name, float height, float width, float movespeed, float jumpspeed = 8.0f, mVector3 pos = mVector3(0.0), mVector3 rot = mVector3(0.0), mVector3 dir = mVector3(0.0));
	~CharacterController();

	/**
	 * Initiate CharController if model isn't needed. Creates a capsule collider from mwidth and mheight
	 * It's used when the CC doesn't need model (good for player)
	 */
	void initCharacterController();
	/**
	 * Initiate CC when model is needed. It's using the model's box collider.
	 * 
	 * \param model
	 */
	void initCharacterController(Model model);

	/**
	 * Updates the CC. Sets the walk direction of the CC and updates it's position by the simulated one.
	 * 
	 */
	void update();


	/**
	 * Calculates the front and right vector.
	 * 
	 */
	void calculateFrontAndRight();
};


#endif // !CHARACTERCONTROLLER_H

