#ifndef AABB_H
#define AABB_H

#include <iostream>
#include <glm/glm.hpp>

/**
 * Stores AABB of Meshes or Models.
 */
class AABB
{
	float minX, maxX;
	float minY, maxY;
	float minZ, maxZ;

	float width, height, depth;

public:
	AABB();
	AABB(float minx, float maxx, float miny, float maxy, float minz, float maxz);


	float getWidth();
	float getHeight();
	float getDepth();

	AABB& operator=(const AABB& rhs);
};


#endif // !AABB_H
