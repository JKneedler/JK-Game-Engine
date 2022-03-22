#include "AssetLoader.h"

AssetLoader::AssetLoader(AssetCache* assetCache) {
	this->assetCache = assetCache;
}

void AssetLoader::Initialize(const char* textureMapLoc, const char* shaderMapLoc) {
	CreateTextureAssetMap(textureMapLoc);
	CreateShaderAssetMap(shaderMapLoc);
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

void AssetLoader::CreateShaderAssetMap(const char* shaderMapLoc) {
	std::ifstream i(shaderMapLoc);
	json j;
	i >> j;
	for (auto it : j.items()) {
		shaderMap.insert({ it.key().c_str(), it.value().dump().c_str() });
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
	std::string geometricLoc = j["geometric_location"].get<std::string>();

	Shader* shader = new Shader();
	if (!geometricLoc.empty()) {
		shader->CreateFromFiles(vertexLoc.c_str(), geometricLoc.c_str(), fragmentLoc.c_str());
	}
	else {
		shader->CreateFromFiles(vertexLoc.c_str(), fragmentLoc.c_str());
	}

	return shader;
}

AssetLoader::~AssetLoader() {
}
