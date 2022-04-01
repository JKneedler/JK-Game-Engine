#include "MeshRenderer.h"

MeshRenderer::MeshRenderer() : BaseComponent() {
}

MeshRenderer::MeshRenderer(std::vector<Mesh*> myMeshes, std::vector<Material*> myMaterials) : BaseComponent() {
	meshes = myMeshes;
	materials = myMaterials;
}

void MeshRenderer::Initialize() {}

void MeshRenderer::Start() {}

void MeshRenderer::Update() {}

void MeshRenderer::Render() {
	for (size_t i = 0; i < meshes.size(); i++) {
		materials[i]->UseMaterial();
		gameObject->transform->SetModel(materials[i]->GetShader()->GetModelLocation());
		meshes[i]->RenderMesh();
	}
}

void MeshRenderer::Render(Shader* shader) {
	for (size_t i = 0; i < meshes.size(); i++) {
		materials[i]->UseMaterial();
		gameObject->transform->SetModel(shader->GetModelLocation());
		meshes[i]->RenderMesh();
	}
}

MeshRenderer::~MeshRenderer() {
}
