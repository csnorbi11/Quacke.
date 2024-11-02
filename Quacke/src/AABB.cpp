#include "AABB.hpp"

AABB::AABB()
	:
	minX(0.0f),
	maxX(0.0f),
	minY(0.0f),
	maxY(0.0f),
	minZ(0.0f),
	maxZ(0.0f),
	width(0.0f),
	height(0.0f),
	depth(0.0f)
{
}

AABB::AABB(float minx, float maxx, float miny, float maxy, float minz, float maxz)
	:
	minX(minx),
	maxX(maxx),
	minY(miny),
	maxY(maxz),
	minZ(minz),
	maxZ(maxz),
	width(0.0f),
	height(0.0f),
	depth(0.0f)
{
	width = (abs(minx) + abs(maxx)) / 2;
	height = (abs(miny) + abs(maxy)) / 2;
	depth = (abs(minz) + abs(maxz)) / 2;
}

float AABB::getWidth()
{
	return width;
}

float AABB::getHeight()
{
	return height;
}

float AABB::getDepth()
{
	return depth;
}

AABB& AABB::operator=(const AABB& rhs)
{
	if (this == &rhs)
		return *this;

	minX = rhs.minX;
	maxX = rhs.maxX;
	minY = rhs.minY;
	maxY = rhs.maxY;
	minZ = rhs.minZ;
	maxZ = rhs.maxZ;
	width = rhs.width;
	height = rhs.height;
	depth = rhs.depth;

	return *this;

}
