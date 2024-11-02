#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture
{
public:
	unsigned int ID;
	std::string path;
	const char* type;
public:

	Texture(std::string path, const char* typ);
	~Texture();
	void useTexture();
};

#endif // !TEXTURE_H
