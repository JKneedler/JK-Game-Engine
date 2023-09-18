#include "AssetCache.h"

AssetCache::AssetCache() {
}

void AssetCache::Initialize(const char* textureMapLoc, const char* shaderMapLoc, const char* modelMapLoc, const char* materialMapLoc) {
	assetLoader = new AssetLoader(this);
	assetLoader->Initialize(textureMapLoc, shaderMapLoc, modelMapLoc, materialMapLoc);
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

Shader* AssetCache::LoadShader(const char* shaderKey) {
	std::cout << "ShaderKey: " << shaderKey << std::endl;
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

ModelData* AssetCache::LoadModelData(const char* modelKey) {
	std::cout << "ModelKey: " << modelKey << std::endl;
	std::map<std::string, ModelData*>::iterator it = modelMap.find(modelKey);
	ModelData* modelData;

	if (it != modelMap.end()) {
		std::cout << "Model for {" << modelKey << "} found in Cache" << std::endl;
		modelData = it->second;
	}
	else {
		std::cout << "Model for {" << modelKey << "} not found in Cache : Loading from AssetLoader" << std::endl;
		modelData = assetLoader->LoadModelData(modelKey);
		modelMap.insert({ modelKey, modelData });
	}
	return modelData;
}

Material* AssetCache::LoadMaterial(const char* materialKey) {
	std::cout << "MaterialKey: " << materialKey << std::endl;
	std::map<std::string, Material*>::iterator it = materialMap.find(materialKey);
	Material* material;

	if (it != materialMap.end()) {
		std::cout << "Material for {" << materialKey << "} found in Cache" << std::endl;
		material = it->second;
	}
	else {
		std::cout << "Material for {" << materialKey << "} not found in Cache : Loading from AssetLoader" << std::endl;
		material = assetLoader->LoadMaterial(materialKey);
		materialMap.insert({ materialKey, material });
	}
	return material;
}

AssetCache::~AssetCache() {
}
