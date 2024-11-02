#include "Shader.hpp"


Shader::Shader(const char* vertSSP, const char* fragSSP)
	:
	ID(0)
{
	try {
		//Fajlbol betolti a vertex shader es fragment shader source fajljait
		std::ifstream vertexFile, fragmentFile;
		std::stringstream vertexFileBuffer, fragmentFileBuffer;
		std::string vertexCode, fragmentCode;

		vertexFile.open(vertSSP);
		if (!vertexFile.is_open())
		{
			throw "Nem tudta beolvasni a vertex shader source fájlját";
		}
		fragmentFile.open(fragSSP);
		if (!fragmentFile.is_open())
		{
			throw "Nem tudta beolvasni a fragment shader source fájlját";
		}

		vertexFileBuffer << vertexFile.rdbuf();
		fragmentFileBuffer << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertexCode = vertexFileBuffer.str();
		fragmentCode = fragmentFileBuffer.str();

		const char* vertexShaderSource = vertexCode.c_str();
		const char* fragmentShaderSource = fragmentCode.c_str();


		int success;
		char infoLog[512];


		unsigned int vertexShader, fragmentShader;
		//letrehozza a shadereket
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		//csatolja a shaderekhez a source fajlokat
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		//leforditja a shadereket
		glCompileShader(vertexShader);
		glCompileShader(fragmentShader);
		//vertex shader hibakezeles
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "Nem sikerult a vertex shadert leforditani: ";
			throw infoLog;
		}
		//fragment shader hibakezeles
		glad_glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "Nem sikerult a fragment shadert leforditani: ";
			throw infoLog;
		}
		//shader program letrehozasa
		ID = glCreateProgram();
		//shaderek hozzacsatolasa a programhoz
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);
		//shader program hibakezelese
		glGetShaderiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID, 512, NULL, infoLog);
			std::cout << "Nem sikerult a shader programot linkelni: ";
			throw infoLog;
		}
		//a mar felesleges shadereket torli
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glUseProgram(ID);
	}
	catch (const char* s)
	{
		std::cout << s << std::endl;
	}
}

Shader::~Shader()
{
	
}

void Shader::use() const
{
	glUseProgram(ID);
}

GLuint Shader::getID() const
{
	return ID;
}

void Shader::setFloat(const char* varName, GLfloat value)
{
	glUniform1f(glGetUniformLocation(ID, varName), value);
}

void Shader::setInt(const char* varName, GLint value)
{
	glUniform1i(glGetUniformLocation(ID, varName), value);
}

void Shader::setUInt(const char* varName, GLuint value)
{
	glUniform1ui(glGetUniformLocation(ID, varName), value);
}

void Shader::setBool(const char* varName, GLboolean value)
{
	glUniform1i(glGetUniformLocation(ID, varName), value);
}

void Shader::setMat4(const char* varName, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, varName), 1, GL_FALSE, &value[0][0]);
}

void Shader::setVec3(const char* varName, glm::vec3 value)
{
	glUniform3fv(glGetUniformLocation(ID, varName), 1, &value[0]);
}
