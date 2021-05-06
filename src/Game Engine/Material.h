#pragma once

#include <GL/glew.h>

#include "Texture.h"
#include "Shader.h"

class Material
{
public:
	Material();
	Material(GLfloat sIntensity, GLfloat shine);
	Material(Shader* myShader, Texture* myTexture,GLfloat sIntensity, GLfloat shine);

	void UseMaterial();
	void UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);

	Shader* GetShader() { return shader; };

	~Material();

private:
	Shader* shader;
	Texture* texture;
	GLfloat specularIntensity;
	GLfloat shininess;
};

