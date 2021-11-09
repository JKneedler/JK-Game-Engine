#include "Scene.h"

Scene::Scene() {
	objectList = std::vector<GameObject*>();
	meshList = std::vector<MeshRenderer*>();

	pointLightCount = 0;
	spotLightCount = 0;
}

void Scene::SetLights(Shader* shader) {
	shader->SetDirectionalLight(mainLight);
	shader->SetPointLights(pointLights, pointLightCount, 3, 0);
	shader->SetSpotLights(spotLights, spotLightCount, 3 + pointLightCount, pointLightCount);
}

void Scene::AddGameObject(GameObject* newObj) {
	objectList.push_back(newObj);
	if (newObj->HasComponent(TYPES::MESH_RENDERER)) {
		MeshRenderer* meshRenderer = (MeshRenderer*)newObj->GetComponent(TYPES::MESH_RENDERER);
		meshList.push_back(meshRenderer);
	}
}

void Scene::AddDirectionalLight(DirectionalLight* directLight) {
	mainLight = directLight;
}

void Scene::AddPointLight(PointLight* pointLight) {
	if (pointLightCount < MAX_POINT_LIGHTS) {
		pointLights[pointLightCount] = pointLight;
		pointLightCount++;
	}
}

void Scene::AddSpotLight(SpotLight* spotLight) {
	if (spotLightCount < MAX_SPOT_LIGHTS) {
		spotLights[spotLightCount] = spotLight;
		spotLightCount++;
	}
}

void Scene::SetSkybox(Skybox* setSkybox) {
	skybox = setSkybox;
}

void Scene::Initialize() {
	for (size_t i = 0; i < objectList.size(); i++) {
		objectList[i]->Initialize();
	}
}

void Scene::Update() {
	Camera::mainCamera->Update();
	for (size_t i = 0; i < objectList.size(); i++) {
		objectList[i]->Update();
	}
}

void Scene::DirectionalShadowRender() {
	directionalShadowShader->UseShader();
	glViewport(0, 0, mainLight->GetShadowMap()->GetShadowWidth(), mainLight->GetShadowMap()->GetShadowHeight());

	mainLight->GetShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);

	directionalShadowShader->SetDirectionalLightTransform(mainLight->CalculateLightTransform());

	directionalShadowShader->Validate();
	for (size_t i = 0; i < meshList.size(); i++) {
		meshList[i]->Render(directionalShadowShader);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Scene::OmniShadowLightPass(PointLight* light) {
	omniShadowShader->UseShader();
	glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

	light->GetShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);

	GLuint uniformOmniLightPos = omniShadowShader->GetOmniLightPosLocation();
	GLuint uniformFarPlane = omniShadowShader->GetFarPlaneLocation();

	glm::vec3 position = light->GetGameObject()->transform->getPosition();
	glUniform3f(uniformOmniLightPos, position.x, position.y, position.z);
	glUniform1f(uniformFarPlane, light->GetFarPlane());
	omniShadowShader->SetLightMatrices(light->CalculateLightTransform());

	omniShadowShader->Validate();
	for (size_t i = 0; i < meshList.size(); i++) {
		meshList[i]->Render(omniShadowShader);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Scene::OmniShadowRender() {
	for (size_t i = 0; i < pointLightCount; i++) {
		OmniShadowLightPass(pointLights[i]);
	}
	for (size_t i = 0; i < spotLightCount; i++) {
		OmniShadowLightPass(spotLights[i]);
	}
}

void Scene::Render() {
	// Sort this by each shader, not by each object

	// Clear window
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox->DrawSkybox(Camera::mainCamera->calculateViewMatrix(), Camera::mainCamera->getProjection());

	for (size_t i = 0; i < meshList .size(); i++) {
		Shader* shader = meshList[i]->getMaterial()->GetShader();
		shader->Validate();
		shader->UseShader();
		Camera::mainCamera->SetUniforms(shader->GetProjectionLocation(), shader->GetViewLocation(), shader->GetEyePositionLocation());
		SetLights(shader);
		shader->SetDirectionalLightTransform(mainLight->CalculateLightTransform());
		mainLight->GetShadowMap()->Read(GL_TEXTURE2);
		shader->SetTexture(1);
		shader->SetDirectionalShadowMap(2);
		meshList[i]->Render();
	}
}

Scene::~Scene() {
}
