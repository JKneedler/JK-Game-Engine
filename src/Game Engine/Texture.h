#pragma once

#include <GL/glew.h>

#include "CommonValues.h"
#include <string>

class Texture
{
public:
	Texture();
	Texture(const char* fileLoc);

	bool LoadTexture();

	void UseTexture();
	void ClearTexture();

	~Texture();

private:
	GLuint textureID;
	int width, height, bitDepth;

	char fileLocation[100] = "";
};

