#pragma once

#include <vector>
#include <string>

#include "GameObject/GameObject.h"
#include "Skybox.h"

class World {
public:
	World();

	void LoadSceneAdditive(const char* sceneData);

	void Initialize();
	void Update();
	void ShadowRender();
	void Render();

	~World();

private:
	std::vector<GameObject> gameObjects;

	unsigned int pointLightCount;
	unsigned int spotLightCount;
	DirectionalLight* mainLight;
	PointLight* pointLights[MAX_POINT_LIGHTS];
	SpotLight* spotLights[MAX_SPOT_LIGHTS];

	Skybox* skybox;
};

