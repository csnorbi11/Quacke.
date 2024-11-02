#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <bullet/btBulletCollisionCommon.h>

#include "Mesh.hpp"
#include "AABB.hpp"

/**
 * Model which contains it's meshes, and creates the colliders.
 */
class Model {
	std::vector<Mesh> meshes;
	const char* path;

	std::vector<Texture> loadedTexture;

	//for static entities
	btCompoundShape* compoundCollider;
	
	btConvexShape* boxCollider;

public:
	Model(const char* path);
	~Model();

	void Draw(Shader& shader)
	{
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			
			meshes[i].Draw(shader);
		}
	}

	btCompoundShape* getCompoundCollider();
	btConvexShape* getBoxCollider();

private:
	/**
	 * Loads model.
	 * 
	 * \param path
	 */
	void loadModel(const char* path);
	/**
	 * Process node?.
	 * 
	 * \param node
	 * \param scene
	 */
	void processNode(aiNode* node, const aiScene* scene);
	/**
	 * Process a single mesh of the model.
	 * 
	 * \param mesh
	 * \param scene
	 * \return 
	 */
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	/**
	 * Loads material's textures but checks if the texture already loaded.
	 * 
	 * \param mat
	 * \param type
	 * \param typeName
	 * \return 
	 */
	std::vector<Texture> loadMaterialtoTexture(aiMaterial* mat, aiTextureType type, const char* typeName);
	
	
};

#endif // !MODEL_H
