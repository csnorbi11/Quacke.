#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture
{
	std::string path;
	std::string type;
	GLuint ID;
public:

	Texture(std::string path, const char* typ);
	~Texture();
	void useTexture();

	std::string GetPath();
	std::string GetType();
	GLuint GetID();
};

#endif // !TEXTURE_H
