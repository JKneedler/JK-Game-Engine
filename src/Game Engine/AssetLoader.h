#pragma once
// Should be responsible for storing the key/value pairs of assets

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class AssetLoader;

#include "AssetCache.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"
#include "json.hpp"
#include "ModelData.h"

using json = nlohmann::json;
// TODO : Models

class AssetLoader {
public:
	AssetLoader(AssetCache* assetCache);

	void Initialize(const char* textureMapLoc, const char* shaderMapLoc, const char* modelMapLoc, const char* materialMapLoc);

	Texture* LoadTexture(const char* textureKey);
	Shader* LoadShader(const char* shaderKey);
	Material* LoadMaterial(const char* materialKey);
	ModelData* LoadModelData(const char* modelKey);

	~AssetLoader();

private:
	AssetCache* assetCache;
	std::map<std::string, std::string> textureMap;
	std::string defaultTextureLoc;
	std::string baseTextureFolder;
	std::map<std::string, std::string> shaderMap;
	std::string baseShaderFolder;
	std::map < std::string, std::string> modelMap;
	std::string baseModelFolder;
	std::map<std::string, std::string> materialMap;

	void CreateTextureAssetMap(const char* textureMapLoc);
	void CreateShaderAssetMap(const char* shaderMapLoc);
	void CreateModelAssetMap(const char* modelMapLoc);
	void CreateMaterialAssetMap(const char* materialMapLoc);

	ModelData* LoadModelNode(ModelData* modelParent, aiNode* node, const aiScene* scene, const char* modelKey);
	MeshData* LoadNodeMesh(aiMesh* mesh, const aiScene* scene, const char* modelKey);
	//std::string GetMeshTexture(int materialNum, const aiScene* scene, const char* modelKey);
};

