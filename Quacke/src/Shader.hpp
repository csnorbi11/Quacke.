#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

/**
 * Shader program.
 */
class Shader {
	unsigned int ID;

public:
	Shader(const char* vertSSP, const char* fragSSP);
	~Shader();

	void use() const;
	unsigned int getID() const;

	void setFloat(const char* varName, float value);
	void setInt(const char* varName, int value);
	void setBool(const char* varName, bool value);
	void setMat4(const char* varName, glm::mat4 value);
	void setVec3(const char* varName, glm::vec3 value);

};

#endif // !SHADER_H
