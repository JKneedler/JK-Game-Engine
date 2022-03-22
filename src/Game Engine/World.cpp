#include "World.h"

World::World() {
}

// I need to add every individual GameObject and children to the gameObjects list because they need to exist here as items on the stack
void World::LoadSceneAdditive(const char* sceneData) {
}

void World::Initialize() {
	for (size_t i = 0; i < gameObjects.size(); i++) {
		gameObjects[i].Initialize();
	}
}

void World::Update() {
	Camera::mainCamera->Update();
	for (size_t i = 0; i < gameObjects.size(); i++) {
		gameObjects[i].Update();
	}
}

void World::ShadowRender() {
}

void World::DirectionalShadowRender() {
	directionalShadowShader->UseShader();
	glViewport(0, 0, mainLight->GetShadowMap()->GetShadowWidth(), mainLight->GetShadowMap()->GetShadowHeight());

	mainLight->GetShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);

	directionalShadowShader->SetDirectionalLightTransform(mainLight->CalculateLightTransform());

	directionalShadowShader->Validate();
	for (size_t i = 0; i < gameObjects.size(); i++) {
		gameObjects[i].Render(directionalShadowShader);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void World::OmniShadowLightPass(PointLight* light) {
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
	for (size_t i = 0; i < gameObjects.size(); i++) {
		gameObjects[i].Render(omniShadowShader);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void World::OmniShadowRender() {
	// Should these methods be stored within the lights and the this method should just be calling it on the lights???
	for (size_t i = 0; i < pointLightCount; i++) {
		OmniShadowLightPass(pointLights[i]);
	}
	for (size_t i = 0; i < spotLightCount; i++) {
		OmniShadowLightPass(spotLights[i]);
	}
}

void World::Render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox->DrawSkybox(Camera::mainCamera->calculateViewMatrix(), Camera::mainCamera->getProjection());
	for (size_t i = 0; i < gameObjects.size(); i++) {
		gameObjects[i].Render();
	}
}

World::~World() {
}
