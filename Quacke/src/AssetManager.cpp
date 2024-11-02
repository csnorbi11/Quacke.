#include "AssetManager.hpp"


AssetManager::AssetManager()
{}

AssetManager::~AssetManager()
{
}

AssetManager& AssetManager::instance()
{
	static AssetManager* _instance = new AssetManager();
	return *_instance;
}

void AssetManager::createShader(const char* shaderName, const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath)
{
	unsigned int key = getKey(shaderName);

	if (!isShaderExists(shaderName))
	{
		Shader shader(vertexShaderSourcePath, fragmentShaderSourcePath);
		shaders.insert(std::pair<unsigned int, Shader>(key, shader));
	}
}

Shader& AssetManager::getShader(const char* shaderName)
{	
	return shaders.at(getKey(shaderName));
}

bool AssetManager::isShaderExists(const char* shaderName)
{
	return shaders.count(getKey(shaderName)) == 0 ? false : true;
}

void AssetManager::createModel(const char* modelPath)
{
	unsigned int key = getKey(modelPath);

	if (!isModelExists(modelPath))
	{
		Model model(modelPath);
		models.insert(std::pair<unsigned int, Model>(key, model));
	}
}

Model& AssetManager::getModel(const char* modelPath)
{
	assert(isModelExists(modelPath));
	return models.at(getKey(modelPath));
}

bool AssetManager::isModelExists(const char* modelPath)
{
	return models.count(getKey(modelPath)) == 0 ? false : true;
}

unsigned int AssetManager::getKey(const char* rsourceName)
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
