#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <iostream>

#include "ResourceManager.hpp"

/**
 * It contains everything (Shader, Model) for Entities which are going to be drawn.
 */
class Drawable {
	ResourceManager rmanager;
	Shader& shader;
	Model& model;

	bool drawable;

public:
	/**
	 * Check that everything exists.
	 *
	 * \param shaderName
	 * \param modelPath
	 */
	Drawable(const char* shaderName, const char* modelPath);
	~Drawable();

	Shader& getShader();
	Model& getModel();

	bool isDrawable() const;
};


#endif // !DRAWABLE_H
