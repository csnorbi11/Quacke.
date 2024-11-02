#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Texture.hpp"
#include "Utilities.hpp"
#include "AABB.hpp"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoord;
};
/**
 * Stores the mesh's data.
 */
class Mesh {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	AABB aabb;

	unsigned int VBO, VAO, EBO;

public:
	Mesh(std::vector<Vertex> verts, std::vector<unsigned int> inds, std::vector<Texture> texs);
	~Mesh();
	/**
	 * Draws it into the buffer.
	 * 
	 * \param shader
	 */
	void Draw(Shader& shader)
	{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		//passes the mesh's textures to the shader program
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			std::string number;
			std::string name = textures[i].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);
			
			shader.setInt((name + number).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, textures[i].ID);
		}
		

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glActiveTexture(GL_TEXTURE0);
	}

	AABB getAABB();
	
private:
	/**
	 * Loads the mesh into the VRAM.
	 * 
	 */
	void setupMesh();

};


#endif // !MESH_H
