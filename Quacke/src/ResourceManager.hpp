#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <assert.h>
#include <map>

#include "Model.hpp"
#include "Shader.hpp"

/**
 * It manages shaders and models. Creates them and check if they are created.
 * 
 */
class ResourceManager
{
	std::map<unsigned int, Shader> shaders;
	std::map<unsigned int, Model> models;

public:
	ResourceManager();
	~ResourceManager();

	static ResourceManager& instance();

	void createShader(const char* shaderName, const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath);
	Shader& getShader(const char* shaderName);
	bool isShaderExists(const char* shaderName);

	void createModel(const char* modelPath);
	Model& getModel(const char* modelPath);
	bool isModelExists(const char* modelPath);


private:
	/**
	 * Creates a key by the name of the resource.
	 * 
	 * \param rsourceName
	 * \return 
	 */
	unsigned int getKey(const char* rsourceName);
};
#endif