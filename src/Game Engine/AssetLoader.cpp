#include "AssetLoader.h"

AssetLoader::AssetLoader(AssetCache* assetCache) {
	this->assetCache = assetCache;
}

void AssetLoader::Initialize(const char* textureMapLoc, const char* materialMapLoc, const char* shaderMapLoc) {
	CreateTextureAssetMap(textureMapLoc);
	CreateShaderAssetMap(shaderMapLoc);
	CreateMaterialAssetMap(materialMapLoc);
}

void AssetLoader::CreateTextureAssetMap(const char* textureMapLoc) {
	std::ifstream i(textureMapLoc);
	json j;
	i >> j;
	for (auto a = j.begin(); a != j.end(); ++a) {
		std::map<std::string, std::string>::iterator iterator = textureMap.begin();
		if (a.key().compare("Default") == 0) {
			std::cout << "Saving default loc" << std::endl;
			defaultTextureLoc = a.value()["fileLoc"].get<std::string>();
		}
		textureMap.insert(iterator, { a.key(), a.value().dump() });
	}
	// To get the actual value of the string without quotes use this = ["fileLoc"].get<std::string>().c_str()
}

void AssetLoader::PrintTextureMap() {
	for (auto itr = textureMap.begin(); itr != textureMap.end(); ++itr) {
		std::cout << itr->first << '\t' << itr->second << std::endl;
	}
}

void AssetLoader::CreateShaderAssetMap(const char* shaderMapLoc) {
	std::ifstream i(shaderMapLoc);
	json j;
	i >> j;
	for (auto it : j.items()) {
		shaderMap.insert({ it.key().c_str(), it.value().dump().c_str() });
	}
}

void AssetLoader::CreateMaterialAssetMap(const char* materialMapLoc) {
	std::ifstream i(materialMapLoc);
	json j;
	i >> j;
	for (auto it : j.items()) {
		materialMap.insert({ it.key().c_str(), it.value().dump().c_str() });
	}
}

Texture* AssetLoader::LoadTexture(const char* textureKey) {
	std::map<std::string, std::string>::iterator it = textureMap.find(textureKey);
	json j;
	std::string fileLoc;

	// Add exception handling here to catch a parsing error and print it back out the console
	if (it != textureMap.end()) {
		j = json::parse(it->second);
		fileLoc = j["fileLoc"].get<std::string>();
	}
	else {
		std::cout << "Texture Map found no result for textureKey {" << textureKey << "} : Default texture used" << std::endl;
		fileLoc = defaultTextureLoc;
	}

	Texture *texture = new Texture(fileLoc.c_str());
	return texture;
}

Shader* AssetLoader::LoadShader(const char* shaderKey) {
	std::map<std::string, std::string>::iterator it = shaderMap.find(shaderKey);
	json j;

	// Add exception handling here to catch a parsing error and print it back out the console
	if (it != shaderMap.end()) {
		j = json::parse(it->second);
	}
	else {
		std::cout << "Shader Map found no result for shaderKey {" << shaderKey << "} : Default shader used" << std::endl;
	}

	std::string vertexLoc = j["vertex_location"].get<std::string>();
	std::string fragmentLoc = j["fragment_location"].get<std::string>();

	Shader* shader = new Shader();
	shader->CreateFromFiles(vertexLoc.c_str(), fragmentLoc.c_str());

	return shader;
}

Material* AssetLoader::LoadMaterial(const char* materialKey) {
	std::map<std::string, std::string>::iterator it = materialMap.find(materialKey);
	json j;

	// Add exception handling here to catch a parsing error and print it back out the console
	if (it != materialMap.end()) {
		j = json::parse(it->second);
	}
	else {
		std::cout << "Material Map found no result for shaderKey {" << materialKey << "} : Default shader used" << std::endl;
	}

	Material material;
	Shader* shader = assetCache->LoadShader(j["shader"].get<std::string>().c_str());
	Texture* texture = assetCache->LoadTexture(j["texture"].get<std::string>().c_str());
	GLfloat specularIntensity = j["specular_intensity"].get<GLfloat>();
	GLfloat shine = j["shine"].get<GLfloat>();

	return new Material(shader, texture, specularIntensity, shine);
}

AssetLoader::~AssetLoader() {
}
