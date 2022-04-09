#pragma once

#include <vector>
#include <string>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Texture.h"
#include "Objects/GameObject/GameObject.h"
#include "Objects/GameObject/Components/MeshRenderer.h"

class ModelLoader {
public:
	ModelLoader();

	void LoadModel(const char* fileName);

	~ModelLoader();

private:

	GameObject* LoadNodeObject(aiNode* node, const aiScene* scene, GameObject parent);
	Mesh* LoadNodeMeshes(aiNode* node, const aiScene* scene);

	void LoadNode(aiNode* node, const aiScene* scene);
	void LoadMesh(aiMesh* mesh, const aiScene* scene);
	void LoadMaterials(const aiScene* scene);

	std::vector<Mesh*> meshList;
	std::vector<Texture*> textureList;
	std::vector<unsigned int> meshToTex;

};

