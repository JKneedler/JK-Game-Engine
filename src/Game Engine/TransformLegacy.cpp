#include "TransformLegacy.h"

TransformLegacy::TransformLegacy() {
	modelMesh = nullptr;
	mesh = nullptr;
	shader = nullptr;
	texture = nullptr;
	material = nullptr;
	position = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
	model = glm::mat4(1.0f);
	uniformModel = 0;
}

TransformLegacy::TransformLegacy(Mesh* myMesh, Shader* myShader, Texture* myTexture, Material* myMaterial, glm::vec3 startPos, glm::vec3 startRot, glm::vec3 startScale) {
	modelMesh = nullptr;
	mesh = myMesh;
	shader = myShader;
	texture = myTexture;
	material = myMaterial;
	position = startPos;
	rotation = startRot;
	scale = startScale;
	model = glm::mat4(1.0f);
	uniformModel = 0;
}

TransformLegacy::TransformLegacy(Model* myModel, Shader* myShader, glm::vec3 startPos, glm::vec3 startRot, glm::vec3 startScale) {
	modelMesh = myModel;
	mesh = nullptr;
	shader = myShader;
	texture = nullptr;
	material = nullptr;
	position = startPos;
	rotation = startRot;
	scale = startScale;
	model = glm::mat4(1.0f);
	uniformModel = 0;
}

void TransformLegacy::RenderObject() {
	shader->UseShader();
	uniformModel = shader->GetModelLocation();

	model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, rotation.x * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, rotation.y * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, rotation.z * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, scale);

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));


	if (!modelMesh) {
		uniformSpecularIntensity = shader->GetSpecularIntensityLocation();
		uniformShininess = shader->GetShininessLocation();
		material->UseMaterial(uniformSpecularIntensity, uniformShininess);
		texture->UseTexture();
		mesh->RenderMesh();
	}
	else {
		modelMesh->RenderModel();
	}
}

void TransformLegacy::Translate(glm::vec3 translation) {
	position += translation;
}

TransformLegacy::~TransformLegacy() {

}
