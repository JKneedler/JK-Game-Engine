#pragma once

class SceneManager;

#include "Scene.h"

class SceneManager {

public:
	SceneManager();

	void Initialize();

	void LoadScene(Scene* newScene);
	Scene* getScene();

	void Update();
	void ShadowRender();
	void Render();

	~SceneManager();
private:
	Scene* scene;
};

