#include "Renderer.hpp"

Renderer::Renderer()
{}

Renderer::~Renderer()
{
	
}

Renderer& Renderer::instance()
{
	static Renderer* _instance = new Renderer();
	return *_instance;
}