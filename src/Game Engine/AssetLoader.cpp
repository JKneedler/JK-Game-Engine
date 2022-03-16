#include "AssetLoader.h"

AssetLoader::AssetLoader() {
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

//Shader AssetLoader::LoadShader(const char* shaderKey) {
//	std::map<const char*, const char*>::iterator it = shaderMap.find(shaderKey);
//	json j;
//
//	// Add exception handling here to catch a parsing error and print it back out the console
//	if (it != shaderMap.end())
//		j = json::parse(it);
//
//	std::string vertexLocation = j["vertex_location"].get<std::string>();
//	std::string fragmentLocation = j["fragment_location"].get<std::string>();
//	Shader shader = Shader();
//	shader.CreateFromFiles(vertexLocation.c_str(), fragmentLocation.c_str());
//	return shader;
//}

// Figure out how this constructor will be called while ensuring that the asset manager is able to store the shader and texture created for it
// Maybe this should belong in the Asset manager where it will call out to the AssetLoader to get the info(maybe the json text)
// Should they all belong in the asset manager? Maybe this class should just worry about storing the maps -
// - for the Textures/Shaders/Materials/Scenes/GameObjects/etc.
Material AssetLoader::LoadMaterial(const char* materialKey) {
	return Material();
}

AssetLoader::~AssetLoader() {
}
