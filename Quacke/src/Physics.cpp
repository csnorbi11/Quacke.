#include "Physics.hpp"

Physics* Physics::mInstance = nullptr;

Physics::Physics()
	:
	sweepBP(new btAxisSweep3(btVector3(-1000, -1000, -1000), btVector3(1000, 1000, 1000))),
	collisionConfig(new btDefaultCollisionConfiguration()),
	dispatcher(new btCollisionDispatcher(collisionConfig)),
	overlappingPairCache(sweepBP),
	solver(new btSequentialImpulseConstraintSolver()),
	dynamicsWorld(new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfig)),
	timeSinceLastStep(0.0f),
	simulationTimeStep(1.0f/60.0f)
{
	dynamicsWorld->getDispatchInfo().m_allowedCcdPenetration = 0.00001f;

	sweepBP->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());;
}

Physics::~Physics()
{

}

Physics& Physics::instance()
{
	if (mInstance == nullptr)
		mInstance = new Physics();
	return *mInstance;
}

btDiscreteDynamicsWorld* Physics::getDynamicsWorld()
{
	return dynamicsWorld;
}
