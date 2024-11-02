#include "CharacterController.hpp"

CharacterController::CharacterController()
	:
	Entity(),
	ghostObject(new btPairCachingGhostObject()),
	front(0.0),
	right(0.0),
	mheight(0.0f),
	mwidth(0.0f),
	jumpSpeed(10.0f),
	isAdded(false),
	velocity(0.0),
	moveSpeed(0.0)
{
	transform.setIdentity();
	transform.setOrigin(btVector3(position.x, position.y, position.z));
	ghostObject->setWorldTransform(transform);

	btConvexShape* colShape = new btCapsuleShape(1, 3);
	ghostObject->setCollisionShape(colShape);
	ghostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);

	character = new btKinematicCharacterController(ghostObject, colShape, 0.35, btVector3(0, 1, 0));
	character->setJumpSpeed(8);
}

CharacterController::CharacterController(const char* name, float height, float width, float jumpspeed, float movespeed, mVector3 pos, mVector3 rot, mVector3 dir)
	:
	Entity(name, pos, rot, dir),
	character(nullptr),
	ghostObject(new btPairCachingGhostObject()),
	front(0.0),
	right(0.0),
	mheight(height),
	mwidth(width/2),
	jumpSpeed(jumpspeed),
	isAdded(false),
	velocity(0.0),
	moveSpeed(movespeed)
{

}

CharacterController::~CharacterController()
{

}

void CharacterController::initCharacterController()
{
	transform.setIdentity();
	ghostObject->setWorldTransform(transform);
	

	btConvexShape* colShape = new btCapsuleShape(mwidth, mheight);
	ghostObject->setCollisionShape(colShape);
	ghostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	
	
	character = new btKinematicCharacterController(ghostObject, colShape, 0.35, btVector3(0, 1, 0));
	character->setJumpSpeed(jumpSpeed);
}

void CharacterController::initCharacterController(Model model)
{

	transform.setIdentity();
	ghostObject->setWorldTransform(transform);

	ghostObject->setCollisionShape(model.getBoxCollider());
	ghostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);


	character = new btKinematicCharacterController(ghostObject, model.getBoxCollider(), 0.35, btVector3(0, 1, 0));
	character->setJumpSpeed(jumpSpeed);
}

void CharacterController::update(float physicsFixedDeltaTime, float deltaTime)
{
	character->setWalkDirection(btVector3(velocity.x, velocity.y, velocity.z));
	transform = ghostObject->getWorldTransform();
	position.x = transform.getOrigin().x();
	position.y = transform.getOrigin().y();
	position.z = transform.getOrigin().z();
}

void CharacterController::calculateFrontAndRight()
{
	front.x = cos(glm::radians(rotation.y));
	front.z = sin(glm::radians(rotation.y));
	front = mUtilities::normalize(front);
	right = mUtilities::normalize(mUtilities::cross(front, mVector3(0, 1, 0)));
}