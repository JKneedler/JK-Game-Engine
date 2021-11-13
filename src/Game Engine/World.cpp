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

void World::Render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox->DrawSkybox(Camera::mainCamera->calculateViewMatrix(), Camera::mainCamera->getProjection());
	for (size_t i = 0; i < gameObjects.size(); i++) {
		// Figure out the render situation with the Shaders, need to move that functionality from the Scene to the shaders before I move forward
		gameObjects[i].Render();
	}
}

World::~World() {
}
