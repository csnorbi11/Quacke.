#include "Camera.hpp"

Camera::Camera()
	:
	right(0),
	up(0),
	front(0),
	mouseSensitivity(1),
	character(),
	position(mVector3(0.0)),
	pitch(0),
	yaw(0),
	freeLook(false)
{

}

Camera::~Camera()
{
	character = nullptr;
}



void Camera::update(float deltaTime)
{
	if (character != nullptr)
	{
		position = character->cameraPosition;
		character->rotation.y = yaw;
		character->rotation.x = pitch;
	}


}


glm::mat4 Camera::getView()
{
	glm::vec3 pos(position.x, position.y, position.z);
	glm::vec3 fr(front.x, front.y, front.z);
	glm::vec3 u(up.x, up.y, up.z);
	return glm::lookAt(pos, pos + fr, u);
}

void Camera::processMouse(double& xoffset, double& yoffset)
{
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;


	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;


	calculateView();
}

mVector3 Camera::getFrontVector()
{
	return front;
}

mVector3 Camera::getRightVector()
{
	return right;
}

void Camera::setCharacter(Character* character)
{
	this->character = character;
}

const Character* Camera::getCharacter()
{
	return character;
}

void Camera::calculateView()
{
	//direction vector
	mVector3 dir;
	dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	dir.y = sin(glm::radians(pitch));
	dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	dir.calculateLength();

	front = mUtilities::normalize(dir);
	right = mUtilities::normalize(mUtilities::cross(front, mVector3(0.0, 1.0, 0.0)));
	up = mUtilities::normalize(mUtilities::cross(right, front));
}