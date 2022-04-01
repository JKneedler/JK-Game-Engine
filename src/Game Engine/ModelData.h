#pragma once

#include <vector>
#include <string>
#include <GL/glew.h>

class ModelData;

#include "MeshData.h"

class ModelData {
public:
	ModelData(std::vector<MeshData*> meshes) : meshes(meshes) {};

	std::vector<ModelData*> children;
	std::vector<MeshData*> meshes;
	void AddChild(ModelData* childModel) { children.push_back(childModel); }

	~ModelData() {};
};

