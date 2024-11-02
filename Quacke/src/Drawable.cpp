#include "Drawable.hpp"

Drawable::Drawable(const char* shaderName, const char* modelPath)
	:
	assetManager(assetManager.instance()),
	shader(assetManager.instance().getShader(shaderName)),
	model(assetManager.instance().getModel(modelPath)),
	drawable(false)
{

	if (!assetManager.instance().isShaderExists(shaderName))
	{
		std::cout << "No shaders exists with name of \"" << shaderName << "\"" << std::endl;
		drawable = false;
	}
	else if (!assetManager.instance().isModelExists(modelPath))
	{
		std::cout << "No model exists with path:  \"" << modelPath << "\"" << std::endl;
		drawable = false;
		
	}
	else
	{
		shader = assetManager.instance().getShader(shaderName);
		drawable = true;
	}

}

Drawable::~Drawable()
{
	
}

Shader& Drawable::getShader()
{
	return shader;
}

Model& Drawable::getModel()
{
	return model;
}

bool Drawable::isDrawable() const
{
	return drawable;
}
