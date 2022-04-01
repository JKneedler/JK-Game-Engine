#include "AssetLoader.h"

AssetLoader::AssetLoader(AssetCache* assetCache) {
	this->assetCache = assetCache;
}

void AssetLoader::Initialize(const char* textureMapLoc, const char* shaderMapLoc, const char* modelMapLoc) {
	CreateTextureAssetMap(textureMapLoc);
	CreateShaderAssetMap(shaderMapLoc);
	CreateModelAssetMap(modelMapLoc);
}

void AssetLoader::CreateTextureAssetMap(const char* textureMapLoc) {
	std::ifstream i(textureMapLoc);
	json j;
	i >> j;
	for (auto a = j.begin(); a != j.end(); ++a) {
		std::map<std::string, std::string>::iterator iterator = textureMap.begin();
		if (a.key().compare("Base Folder") == 0) {
			baseTextureFolder = a.value()["FolderLoc"].get<std::string>();
		}
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
		if (it.key().compare("Base Folder") == 0) {
			baseShaderFolder = it.value()["FolderLoc"].get<std::string>();
		}
		shaderMap.insert({ it.key().c_str(), it.value().dump().c_str() });
	}
}

void AssetLoader::CreateModelAssetMap(const char* modelMapLoc) {
	std::ifstream i(modelMapLoc);
	json j;
	i >> j;
	for (auto a = j.begin(); a != j.end(); ++a) {
		std::map<std::string, std::string>::iterator iterator = modelMap.begin();
		if (a.key().compare("Base Folder") == 0) {
			baseModelFolder = a.value()["FolderLoc"].get<std::string>();
		}
		modelMap.insert(iterator, { a.key(), a.value().dump() });
	}
}

Texture* AssetLoader::LoadTexture(const char* textureKey) {
	std::map<std::string, std::string>::iterator it = textureMap.find(textureKey);
	json j;
	std::string fileLoc;

	// Add exception handling here to catch a parsing error and print it back out the console
	if (it != textureMap.end()) {
		j = json::parse(it->second);
		fileLoc = baseTextureFolder + j["fileLoc"].get<std::string>();
	}
	else {
		std::cout << "Texture Map found no result for textureKey {" << textureKey << "} : Default texture used" << std::endl;
		fileLoc = baseTextureFolder + defaultTextureLoc;
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

	std::string vertexLoc = baseShaderFolder + j["vertex_location"].get<std::string>();
	std::string fragmentLoc = baseShaderFolder + j["fragment_location"].get<std::string>();
	std::string geometricLoc = baseShaderFolder + j["geometric_location"].get<std::string>();

	Shader* shader = new Shader();
	if (geometricLoc.compare(baseShaderFolder) != 0) {
		shader->CreateFromFiles(vertexLoc.c_str(), geometricLoc.c_str(), fragmentLoc.c_str());
	}
	else {
		shader->CreateFromFiles(vertexLoc.c_str(), fragmentLoc.c_str());
	}

	return shader;
}

ModelData* AssetLoader::LoadModelData(const char* modelKey) {
	std::map<std::string, std::string>::iterator it = modelMap.find(modelKey);
	json j;

	// Add exception handling here to catch a parsing error and print it back out the console
	if (it != modelMap.end()) {
		j = json::parse(it->second);
	}
	else {
		std::cout << "Model Map found no result for modelKey {" << modelKey << "}" << std::endl;
	}

	Assimp::Importer importer;
	std::string modelLoc = baseModelFolder + j["FileLoc"].get<std::string>();
	const aiScene* scene = importer.ReadFile(modelLoc, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
	if (!scene) {
		printf("Model (%s) failed to load: %s", modelLoc.c_str(), importer.GetErrorString());
		return nullptr;
	}

	ModelData* modelData = LoadModelNode(nullptr, scene->mRootNode, scene, modelKey);
	return modelData;
}

ModelData* AssetLoader::LoadModelNode(ModelData* modelParent, aiNode* node, const aiScene* scene, const char* modelKey) {
	ModelData* model = nullptr;
	if (node->mNumMeshes > 0) {
		std::vector<MeshData*> meshes;
		for (size_t i = 0; i < node->mNumMeshes; i++) {
			printf("Mesh (%d) loading...", i);
			MeshData* mesh = LoadNodeMesh(scene->mMeshes[node->mMeshes[i]], scene, modelKey);
			meshes.push_back(mesh);
		}
		model = new ModelData(meshes);
	}


	if (model == nullptr && modelParent == nullptr && node->mNumChildren > 1) {
		model = new ModelData(std::vector<MeshData*>());
	}

	for (size_t i = 0; i < node->mNumChildren; i++) {
		printf("Going to children...");
		ModelData* child = LoadModelNode((model != nullptr ? model : modelParent), node->mChildren[i], scene, modelKey);

		if (child != nullptr) {
			if (model != nullptr) {
				model->AddChild(child);
			}
			else if (modelParent != nullptr) {
				modelParent->AddChild(child);
			}
			else if (node->mNumChildren == 1) {
				model = child;
			}
		}
	}

	return model;
}

MeshData* AssetLoader::LoadNodeMesh(aiMesh* mesh, const aiScene* scene, const char* modelKey) {
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;

	for (size_t i = 0; i < mesh->mNumVertices; i++) {
		vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });
		if (mesh->mTextureCoords[0]) {
			vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
		}
		else {
			vertices.insert(vertices.end(), { 0.0f, 0.0f });
		}
		vertices.insert(vertices.end(), { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z });
	}

	for (size_t i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	std::string textureLoc = GetMeshTexture(mesh->mMaterialIndex, scene, modelKey);
	MeshData* meshData = new MeshData(vertices, indices, textureLoc);
	return meshData;
}

std::string AssetLoader::GetMeshTexture(int materialNum, const aiScene* scene, const char* modelKey) {
	aiMaterial* material = scene->mMaterials[materialNum];

	std::string texPath = "Assets/Textures/Plain.png";

	if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
		aiString path;
		if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
			int idx = std::string(path.data).rfind("\\");
			std::string filename = std::string(path.data).substr(idx + 1);

			texPath = std::string("Assets/Textures/") + modelKey + std::string("/") + filename;
		}
	}
	return texPath;
}

AssetLoader::~AssetLoader() {
}
