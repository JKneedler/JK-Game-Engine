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

	GLfloat cubeVertices[112] = {
		//   x		y	  z			u	  v				nx	  ny    nz
			0.0f, 1.0f, 0.0f,		0.0f, 0.66f,		0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f,		0.25f, 0.66f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 1.0f,		0.0f, 0.33f,		0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f,		0.25f, 0.33f,		0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,		0.5f, 0.66f,		0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f,		0.75f, 0.66f,		0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 1.0f,		0.5f, 0.33f,		0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 1.0f,		0.75f, 0.33f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		1.0f, 0.66f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 1.0f,		1.0f, 0.33f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.25f, 1.0f,		0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f,		0.5f, 1.0f,			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 1.0f,		0.25f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 1.0f,		0.5f, 0.0f,			0.0f, 0.0f, 0.0f
	};

	unsigned int cubeIndices[36] = {
		0, 2, 1,
		1, 2, 3,
		4, 6, 5,
		6, 7, 5,
		1, 3, 6,
		6, 4, 1,
		8, 5, 7,
		8, 7, 9,
		11, 1, 4,
		10, 1, 11,
		3, 12, 13,
		13, 6, 3
	};

	// I think this is multiplied so that the texture won't stretch when scaled up
	// TODO : adjust either the mesh object or the material to determine the scale/stretch of the texture
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

