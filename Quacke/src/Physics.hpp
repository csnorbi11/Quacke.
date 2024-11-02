#ifndef PHYSICS_H
#define PHYSICS_H

#include <iostream>
#include <assert.h>
#include <vector>

#include "Rigidbody.hpp"
#include "Player.hpp"


/**
 * It runs the physics engine. Contains everything for simulation.
 */
class Physics
{
	btAxisSweep3* sweepBP;
	static Physics* mInstance;

	btDefaultCollisionConfiguration* collisionConfig;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;

	float timeSinceLastStep;

	float simulationTimeStep;


public:
	Physics();
	~Physics();

	static Physics& instance();

	btDiscreteDynamicsWorld* getDynamicsWorld();

	/**
	 * It steps the simulation and updates every member of it.
	 * 
	 * \param player
	 * \param rigidbodies
	 * \param enemies
	 * \param deltaTime
	 */
	template<typename T, typename S>
	void updatePhysics(Player& player, std::vector<T>& rigidbodies, std::vector<S>& enemies, float deltaTime)
	{
		assert((std::is_base_of<Rigidbody, T>::value == 1));
		assert((std::is_base_of<CharacterController, S>::value == 1));

		dynamicsWorld->stepSimulation(simulationTimeStep, 10);		

		
		for (unsigned int i = 0; i < rigidbodies.size(); i++)
		{
			if (!rigidbodies[i].partOfWorld)
			{
				dynamicsWorld->addRigidBody(rigidbodies[i].rigidbody);
				rigidbodies[i].partOfWorld = true;
			}
			rigidbodies[i].updateRigidbody();
		}
		if (!player.isAdded)
		{
			player.isAdded = true;

			dynamicsWorld->addCollisionObject(player.ghostObject, btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter | btBroadphaseProxy::CharacterFilter);
			dynamicsWorld->addAction(player.character);
		}
		for (unsigned int i = 0; i < enemies.size(); i++)
		{
			if (!enemies[i].isAdded)
			{
				enemies[i].isAdded = true;

				dynamicsWorld->addCollisionObject(enemies[i].ghostObject, btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter | btBroadphaseProxy::CharacterFilter);
				dynamicsWorld->addAction(enemies[i].character);
			}
			enemies[i].update(1);
		}


	}
};

#endif // !PHYSICS_H