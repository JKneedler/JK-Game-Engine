#pragma once

#include "Scene.h"

class SceneManager {

public:
	SceneManager();

	void Initialize();

	void LoadScene(Scene* newScene);

	void Update();
	void ShadowRender();
	void Render();

	~SceneManager();
private:
	Scene* scene;
};

