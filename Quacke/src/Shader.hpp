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
	GLuint ID;

public:
	Shader(const char* vertSSP, const char* fragSSP);
	~Shader();

	void use() const;
	GLuint getID() const;

	void setFloat(const char* varName, GLfloat GLfloat);
	void setInt(const char* varName, GLint value);
	void setUInt(const char* varName, GLuint value);
	void setBool(const char* varName, GLboolean value);
	void setMat4(const char* varName, glm::mat4 value);
	void setVec3(const char* varName, glm::vec3 value);

};

#endif // !SHADER_H
