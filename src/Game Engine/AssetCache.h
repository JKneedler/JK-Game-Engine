#pragma once
// Should be responsible for storing the key/value pairs of assets

#include <map>
#include <string>
#include <iostream>
#include <fstream>

class AssetCache;

#include "Texture.h"
#include "Shader.h"
#include "Material.h"
#include "AssetLoader.h"
#include "json.hpp"

using json = nlohmann::json;
// TODO : Models

class AssetCache {
public:
	AssetCache();

	void Initialize(const char* textureMapLoc, const char* shaderMapLoc);

	Texture* LoadTexture(const char* textureKey);
	Shader* LoadShader(const char* shaderKey);

	~AssetCache();

private:

	AssetLoader* assetLoader;
	std::map<std::string, Texture*> textureMap;
	std::map<std::string, Shader*> shaderMap;
};

