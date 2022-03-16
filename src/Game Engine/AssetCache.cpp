#include "AssetCache.h"

AssetCache::AssetCache() {
}

void AssetCache::Initialize(const char* textureMapLoc, const char* materialMapLoc, const char* shaderMapLoc) {
	assetLoader = new AssetLoader();
	assetLoader->Initialize(textureMapLoc, materialMapLoc, shaderMapLoc);
}

Texture* AssetCache::LoadTexture(const char* textureKey) {
	std::cout << "TextureKey: " << textureKey << std::endl;
	std::map<std::string, Texture*>::iterator it = textureMap.find(textureKey);
	Texture* texture;

	if (it != textureMap.end()) {
		std::cout << "Texture for {" << textureKey << "} found in Cache" << std::endl;
		texture = it->second;
	}
	else {
		std::cout << "Texture for {" << textureKey << "} not found in Cache : Loading from AssetLoader" << std::endl;
		texture = assetLoader->LoadTexture(textureKey);
		textureMap.insert({ textureKey, texture });
	}
	return texture;
}

Shader AssetCache::LoadShader(const char* shaderKey) {
	return Shader();
}

Material AssetCache::LoadMaterial(const char* materialKey) {
	return Material();
}

AssetCache::~AssetCache() {
}
