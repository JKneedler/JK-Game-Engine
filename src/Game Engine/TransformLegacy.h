#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Model.h"

class TransformLegacy
{
public:
	TransformLegacy();
	TransformLegacy(Mesh* myMesh, Shader* myShader, Texture* texture, Material* material, glm::vec3 startPos, glm::vec3 startRot, glm::vec3 startScale);
	TransformLegacy(Model* myModel, Shader* myShader, glm::vec3 startPos, glm::vec3 startRot, glm::vec3 startScale);

	void RenderObject();

	void Translate(glm::vec3 translation);

	~TransformLegacy();

private:
	Model* modelMesh;
	Mesh* mesh;
	Shader* shader;
	Texture* texture;
	Material* material;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 model;
	GLuint uniformModel, uniformSpecularIntensity, uniformShininess;
	const float toRadians = 3.14159265f / 180.0f;
};

