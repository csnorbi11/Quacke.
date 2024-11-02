#include "ResourceManager.hpp"


ResourceManager::ResourceManager()
{}

ResourceManager::~ResourceManager()
{
}

ResourceManager& ResourceManager::instance()
{
	static ResourceManager* _instance = new ResourceManager();
	return *_instance;
}

void ResourceManager::createShader(const char* shaderName, const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath)
{
	unsigned int key = getKey(shaderName);

	if (!isShaderExists(shaderName))
	{
		Shader shader(vertexShaderSourcePath, fragmentShaderSourcePath);
		shaders.insert(std::pair<unsigned int, Shader>(key, shader));
	}
}

Shader& ResourceManager::getShader(const char* shaderName)
{	
	return shaders.at(getKey(shaderName));
}

bool ResourceManager::isShaderExists(const char* shaderName)
{
	return shaders.count(getKey(shaderName)) == 0 ? false : true;
}

void ResourceManager::createModel(const char* modelPath)
{
	unsigned int key = getKey(modelPath);

	if (!isModelExists(modelPath))
	{
		Model model(modelPath);
		models.insert(std::pair<unsigned int, Model>(key, model));
	}
}

Model& ResourceManager::getModel(const char* modelPath)
{
	assert(isModelExists(modelPath));
	return models.at(getKey(modelPath));
}

bool ResourceManager::isModelExists(const char* modelPath)
{
	return models.count(getKey(modelPath)) == 0 ? false : true;
}

unsigned int ResourceManager::getKey(const char* rsourceName)
{
	unsigned int key = 0;
	int i = 0;
	while (rsourceName[i] != '\0')
	{
		key += rsourceName[i];
		i++;
	}
	return key;
}
