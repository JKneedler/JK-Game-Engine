#include "MeshRenderer.h"

MeshRenderer::MeshRenderer() : BaseComponent() {
}

MeshRenderer::MeshRenderer(Mesh* myMesh, Material* myMaterial) : BaseComponent() {
	mesh = myMesh;
	material = myMaterial;
}

void MeshRenderer::Initialize() {}

void MeshRenderer::Start() {}

void MeshRenderer::Update() {}

void MeshRenderer::Render() {
	material->UseMaterial();
	gameObject->transform->SetModel(material->GetShader()->GetModelLocation());
	mesh->RenderMesh();
}

void MeshRenderer::Render(Shader* shader) {
	material->UseMaterial(shader->GetSpecularIntensityLocation(), shader->GetShininessLocation());
	gameObject->transform->SetModel(shader->GetModelLocation());
	mesh->RenderMesh();
}

MeshRenderer::~MeshRenderer() {
}
