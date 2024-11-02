#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <assert.h>

#include <glm/gtc/matrix_transform.hpp>

#include <bullet/btBulletDynamicsCommon.h>

#include "Drawable.hpp"

class Renderer {

public:
	Renderer();
	~Renderer();

	static Renderer& instance();
	
	template<typename T>
	void render(std::vector<T>& toRender);
};

#endif // !RENDERER_H

/**
 * Renders passed param.
 * 
 * \param toRender
 */
template<typename T>
void Renderer::render(std::vector<T>& toRender)
{
	assert((std::is_base_of<Drawable, T>::value == 1));

	for (unsigned int i = 0; i < toRender.size(); i++)
	{
		if (toRender[i].isDrawable())
		{
			glm::mat4 modelMatrix = glm::mat4(1.0f);
			glm::vec3 pos(toRender[i].position.x, toRender[i].position.y, toRender[i].position.z);
			glm::vec3 rot(toRender[i].rotation.x, toRender[i].rotation.y, toRender[i].rotation.z);
			modelMatrix = glm::translate(modelMatrix, pos);
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
			toRender[i].getShader().setMat4("model", modelMatrix);
			toRender[i].getModel().Draw(toRender[i].getShader());
		}
	}
}