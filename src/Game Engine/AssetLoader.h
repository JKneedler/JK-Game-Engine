#pragma once
// Should be responsible for storing the key/value pairs of assets

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

class AssetLoader;

#include "AssetCache.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"
#include "json.hpp"

using json = nlohmann::json;
// TODO : Models

class AssetLoader {
public:
	AssetLoader(AssetCache* assetCache);

	void Initialize(const char* textureMapLoc, const char* shaderMapLoc);

	Texture* LoadTexture(const char* textureKey);
	Shader* LoadShader(const char* shaderKey);

	~AssetLoader();

private:
	AssetCache* assetCache;
	std::map<std::string, std::string> textureMap;
	std::string defaultTextureLoc;
	std::map<std::string, std::string> shaderMap;

	void CreateTextureAssetMap(const char* textureMapLoc);
	void CreateShaderAssetMap(const char* shaderMapLoc);
};

