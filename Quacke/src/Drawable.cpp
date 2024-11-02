#include "Drawable.hpp"

Drawable::Drawable(const char* shaderName, const char* modelPath)
	:
	rmanager(rmanager.instance()),
	shader(rmanager.instance().getShader(shaderName)),
	model(rmanager.instance().getModel(modelPath)),
	drawable(false)
{

	if (!rmanager.instance().isShaderExists(shaderName))
	{
		std::cout << "No shaders exists with name of \"" << shaderName << "\"" << std::endl;
		drawable = false;
	}
	else if (!rmanager.instance().isModelExists(modelPath))
	{
		std::cout << "No model exists with path:  \"" << modelPath << "\"" << std::endl;
		drawable = false;
		
	}
	else
	{
		shader = rmanager.instance().getShader(shaderName);
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
