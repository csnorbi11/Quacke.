#include "Model.hpp"

Model::Model(const char* path)
	:
	path(path),
	compoundCollider(new btCompoundShape())
{
	loadModel(this->path);
}

Model::~Model()
{
	
}

void Model::Draw(Shader& shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}
}

btCompoundShape* Model::getCompoundCollider()
{
	return compoundCollider;
}

btConvexShape* Model::getBoxCollider()
{
	return boxCollider;
}

void Model::loadModel(const char* path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}

	this->path = path;
	
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> verts;
	std::vector<unsigned int> inds;
	std::vector<Texture> texs;

	btConvexHullShape* hullShape = new btConvexHullShape();
	btTransform hullShapeTransform;
	hullShapeTransform.setIdentity();
	hullShapeTransform.setOrigin(btVector3(0, 0, 0));

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		hullShape->addPoint(btVector3(vector.x, vector.y, vector.z));
		
		if(mesh->HasNormals())
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
		}

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoord = vec;
		}
		else
			vertex.TexCoord = glm::vec2(0.0f);

		verts.push_back(vertex);
	}

	btVector3 minAABB, maxAABB;
	
	hullShape->optimizeConvexHull();
	compoundCollider->addChildShape(hullShapeTransform, hullShape);
	compoundCollider->getAabb(hullShapeTransform, minAABB, maxAABB);

	AABB tmpAABB(minAABB.x(), maxAABB.x(), minAABB.y(), maxAABB.y(), minAABB.z(), maxAABB.z());

	float height = tmpAABB.getHeight();
	float width = tmpAABB.getWidth();
	float depth = tmpAABB.getDepth();
	boxCollider = new btBoxShape(btVector3(height/2.0, width/2.0, depth));

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			inds.push_back(face.mIndices[j]);
		}
	}


	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	std::vector<Texture> diffuseMaps = loadMaterialtoTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
	texs.insert(texs.end(), diffuseMaps.begin(), diffuseMaps.end());
	std::vector<Texture> specularMaps = loadMaterialtoTexture(material, aiTextureType_SPECULAR, "texture_specular");
	texs.insert(texs.end(), specularMaps.begin(), specularMaps.end());
	
	return Mesh(verts, inds, texs);
}

std::vector<Texture> Model::loadMaterialtoTexture(aiMaterial* mat, aiTextureType type, const char* typeName)
{
	std::vector<Texture> texs;
	
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{

		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < loadedTexture.size(); j++)
		{
			if (std::strcmp(loadedTexture[j].GetPath().data(), str.C_Str()) == 0)
			{
				texs.push_back(loadedTexture[j]);
				skip = true;
				break;
			}
		}
		if(!skip)
		{
			Texture texture(str.C_Str(), typeName);
			texs.push_back(texture);
			loadedTexture.push_back(texture);
		}
	}
	return texs;
}
