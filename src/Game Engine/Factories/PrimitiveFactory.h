#pragma once

class PrimitiveFactory;

#include "../GameObject/GameObject.h"
#include "../GameObject/Components/MeshRenderer.h"
#include "../Mesh.h"

enum PRIMITIVES {
	PLANE,
	PYRAMID,
	CUBE,
};

class PrimitiveFactory {

public:
	PrimitiveFactory();

	Mesh* CreatePrimitive(PRIMITIVES type);

	~PrimitiveFactory();

private:

	void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
		unsigned int vLength, unsigned int normalOffset);

	GLfloat pyramidVertices[32] = {
		//   x		y	  z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int pyramidIndices[12] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat floorVertices[32] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, 1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, 1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, 1.0f, 0.0f
	};

	unsigned int floorIndices[6] = {
		0, 2, 1,
		1, 2, 3
	};

	//const GLfloat cubeVertices[2] = {0.0f, 0.0f};

};

