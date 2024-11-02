#include "Entity.hpp"
#include "Utilities.hpp"

Entity::Entity()
	:
	name(""),
	position(0.0f),
	rotation(0.0f),
	direction(0.0f)
{

}

Entity::Entity(const char* nam, mVector3 pos, mVector3 rot, mVector3 dir)
	:
	name(nam),
	position(pos),
	rotation(rot),
	direction(dir)
{}

Entity::~Entity()
{
	
}

float Entity::calculateDistance(const Entity& target)
{
	float distance = mUtilities::distance(position, target.position);
	return distance;
}

inline const char* Entity::getName()
{
	return name;
}

void Entity::calculateDirection()
{
	direction.x = cos(glm::radians(rotation.y));
	direction.z = sin(glm::radians(rotation.y));
	
}

mVector3 Entity::distanceVector(const Entity& target)
{
	return position - target.position;
}
