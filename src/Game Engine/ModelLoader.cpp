#include "ModelLoader.h"

ModelLoader::ModelLoader() {
}

void ModelLoader::LoadModel(const char* fileName) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (!scene) {
		printf("Model (%s) failed to load: %s", fileName, importer.GetErrorString());
		return;
	}

	std::cout << "================= Start Load =================" << std::endl;







	// I'M OVERTHINKING ALL OF THIS
	//Just focus on the method asking for a GameObject from node comprising of the part of the tree below, THAT'S ALL
	//Pass in the node, scene, and parent GameObject
	// if (node has meshes) {
	// 	   create gameObject with mesh
	// }
	// for (node children) {
	// 	   recursive call to get gameObject from child node
	// 	   if (this node had meshes) {
	//			make the child node gameObject a child of this method gameObject
	// 	   }
	// }
	// return (gameObject with mesh) or (gameObjects returned from recursive call if no meshes) or (nullptr if no mesh and no return from recursive call)



	



	//Have to find a way to avoid a situation where there are a bunch of nodes in a hierarchy without meshes attached
	//Don't want a gameObject for each node, unless there are meshes attached to the node

	// Feed in a nullptr for GameObject variable
	// When done with method, GameObject variable should be filled with model gameObject
	LoadNode(scene->mRootNode, scene);

	LoadMaterials(scene);

	std::cout << "================== End Load ==================" << std::endl;
	std::cout << "# of Meshes: " << meshList.size() << std::endl;
	std::cout << "# of Textures: " << textureList.size() << std::endl;
}

GameObject* ModelLoader::LoadNodeObject(aiNode* node, const aiScene* scene, GameObject parent) {
	if (node->mNumMeshes > 0) {
		for (size_t i = 0; i < node->mNumMeshes; i++) {
			printf("Mesh (%d) loading...\n", i);
			LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
		}
		MeshRenderer* meshRenderer = new MeshRenderer();
		GameObject* meshGameObject = new GameObject();
	}
	return new GameObject();
}

//Need to figure out where the mesh vertices and indices so that they're not lost
//Maybe store the Model Data in the AssetCache(in a ModelData class that stores the vertices/incides of that level and then has children ModelData classes	)

Mesh* ModelLoader::LoadNodeMeshes(aiNode* node, const aiScene* scene) {
	Mesh* mesh = new Mesh();
	//mesh->CreateMesh();
	return mesh;
}

void ModelLoader::LoadNode(aiNode* node, const aiScene* scene) {
	std::cout << "Node Name: " << node->mName.C_Str() << std::endl;
	//Comes in with fed parent GameObject
	//GameObject curNodeObject = fed in gameObject

	//If node has no meshes, skip creating a new gameObject and 
	//just feed in the current gameObject to the LoadNode for the  children

	// if (node has meshes) {
		//Create new gameObject for mesh
		//Combine all Meshes and return a single Mesh.
		//At the end of this for loop there should be a single Mesh
		for (size_t i = 0; i < node->mNumMeshes; i++) {
			printf("Mesh (%d) loading...\n", i);
			LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
		}
		//Add the mesh to a mesh renderer to the gameObject fed in
		// if (fed in gameObject != nullptr) {
			//Add the gameObject as a child to the fed in gameObject
		//}
		//curNodeObject = gameObject with mesh
	//}

	for (size_t i = 0; i < node->mNumChildren; i++) {
		//Feed in the curNodeObject
		printf("Going to child (%d)...\n", i);
		LoadNode(node->mChildren[i], scene);
	}
}

void ModelLoader::LoadMesh(aiMesh* mesh, const aiScene* scene) {		// Creates the leaf node Mesh
	std::cout << "Mesh Name" << mesh->mName.C_Str() << std::endl;
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

	Mesh* newMesh = new Mesh();
	newMesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
	meshList.push_back(newMesh);
	meshToTex.push_back(mesh->mMaterialIndex);					// Finds the material linked to this Mesh based off the index
}

void ModelLoader::LoadMaterials(const aiScene* scene) {				// Loads all materials included in the entire Model at once
	textureList.resize(scene->mNumMaterials);

	for (size_t i = 0; i < scene->mNumMaterials; i++) {
		aiMaterial* material = scene->mMaterials[i];

		textureList[i] = nullptr;

		if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
				int idx = std::string(path.data).rfind("\\");
				std::string filename = std::string(path.data).substr(idx + 1);

				std::string texPath = std::string("Assets/Textures/") + filename;

				textureList[i] = new Texture(texPath.c_str());

				if (!textureList[i]->LoadTexture()) {
					printf("Failed to load texture at: %s\n", texPath);
					delete textureList[i];
					textureList[i] = nullptr;
				}
			}
		}

		if (!textureList[i]) {
			textureList[i] = new Texture("Assets/Textures/plain.png");
			textureList[i]->LoadTexture();
		}
	}
}
