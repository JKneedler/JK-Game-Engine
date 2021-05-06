#include "SceneManager.h"

SceneManager::SceneManager() {
	scene = nullptr;
}

void SceneManager::Initialize() {
	scene->Initialize();
}

void SceneManager::LoadScene(Scene* newScene) {
	scene = newScene;
}

void SceneManager::Update() {
	scene->Update();
}

void SceneManager::ShadowRender() {
	scene->DirectionalShadowRender();
}

void SceneManager::Render() {
	scene->Render();
}

SceneManager::~SceneManager() {
}
