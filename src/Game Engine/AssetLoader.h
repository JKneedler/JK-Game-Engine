#pragma once
// Should be responsible for storing the key/value pairs of assets

#include <map>
#include <string>
#include <iostream>
#include <fstream>

#include "Texture.h"
#include "Shader.h"
#include "Material.h"
#include "json.hpp"

using json = nlohmann::json;
// TODO : Models

class AssetLoader {
public:
	AssetLoader();

	void Initialize(const char* textureMapLoc, const char* materialMapLoc, const char* shaderMapLoc);
	void CreateTextureAssetMap(const char* textureMapLoc);
	void CreateShaderAssetMap(const char* shaderMapLoc);
	void CreateMaterialAssetMap(const char* materialMapLoc);

	Texture LoadTexture(const char* textureKey);
	Shader LoadShader(const char* shaderKey);
	Material LoadMaterial(const char* materialKey);

	~AssetLoader();

private:
	std::map<const char*, const char*> textureMap;
	std::map<const char*, const char*> shaderMap;
	std::map<const char*, const char*> materialMap;
};

