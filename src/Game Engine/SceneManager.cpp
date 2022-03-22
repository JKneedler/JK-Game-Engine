#include "SceneManager.h"

SceneManager::SceneManager() {
	scene = nullptr;
}

void SceneManager::Initialize() {
	scene->Initialize();
}

void SceneManager::LoadScene(Scene* newScene) {
	scene = newScene;
	Camera::mainCamera = scene->getSceneCamera();
}

Scene* SceneManager::getScene() {
	return scene;
}

void SceneManager::Update() {
	scene->Update();
}

void SceneManager::ShadowRender() {
	scene->DirectionalShadowRender();
	scene->OmniShadowRender();
}

void SceneManager::Render() {
	scene->Render();
}

SceneManager::~SceneManager() {
}
