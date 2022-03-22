#include "AssetCache.h"

AssetCache::AssetCache() {
}

void AssetCache::Initialize(const char* textureMapLoc, const char* shaderMapLoc) {
	assetLoader = new AssetLoader(this);
	assetLoader->Initialize(textureMapLoc, shaderMapLoc);
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
	texture->LoadTexture();
	return texture;
}

Shader* AssetCache::LoadShader(const char* shaderKey) {
	std::cout << "TextureKey: " << shaderKey << std::endl;
	std::map<std::string, Shader*>::iterator it = shaderMap.find(shaderKey);
	Shader* shader;

	if (it != shaderMap.end()) {
		std::cout << "Shader for {" << shaderKey << "} found in Cache" << std::endl;
		shader = it->second;
	}
	else {
		std::cout << "Shader for {" << shaderKey << "} not found in Cache : Loading from AssetLoader" << std::endl;
		shader = assetLoader->LoadShader(shaderKey);
		shaderMap.insert({ shaderKey, shader });
	}
	return shader;
}

AssetCache::~AssetCache() {
}
