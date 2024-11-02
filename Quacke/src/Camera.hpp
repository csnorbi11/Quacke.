#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

#include "Player.hpp"

/**
 * Handles camera, process mouse input and calculate the view matrix.
 */
class Camera
{
	mVector3 right;
	mVector3 up;
	mVector3 front;

	float mouseSensitivity;


public:
	mVector3 position;
	float pitch;
	float yaw;
	bool freeLook;

public:
	Camera();
	~Camera();


	void update(float deltaTime, Player& player);

	glm::mat4 getView();
	void processMouse(double& xoffset, double& yoffset);

	mVector3 getFrontVector();
	mVector3 getRightVector();

private:
	void calculateView();
};

#endif // !CAMERA_H
