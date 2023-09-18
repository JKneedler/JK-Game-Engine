 #pragma once

#include <vector>
#include <string>
#include <GL/glew.h>

class MeshData;

#include "Shader.h"

class MeshData {
public:

	MeshData(std::vector<GLfloat> vertices,
		std::vector<unsigned int> indices) :
		vertices(vertices),
		indices(indices) {};

	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;

	~MeshData() {};
};

