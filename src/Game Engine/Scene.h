#pragma once

#include <vector>
#include <string>

#include "Shader.h"
#include "GameObject/Components/MeshRenderer.h"
#include "Skybox.h"

class Scene {
public:
	Scene();

	void SetLights(Shader* shader);

	void SetDirectionalShadowShader(Shader* shader) { directionalShadowShader = shader; }
	void SetOmniShadowShader(Shader* shader) { omniShadowShader = shader; }

	void AddGameObject(GameObject* newObj);
	void AddDirectionalLight(DirectionalLight* directLight);
	void AddPointLight(PointLight* pointLight);
	void AddSpotLight(SpotLight* spotLight);
	void SetSkybox(Skybox* setSkybox);

	void Initialize();
	void Update();
	void DirectionalShadowRender();
	void OmniShadowRender();
	void Render();

	~Scene();

private:
	std::vector<GameObject*> objectList;
	std::vector<MeshRenderer*> meshList;

	unsigned int pointLightCount;
	unsigned int spotLightCount;
	DirectionalLight* mainLight;
	PointLight* pointLights[MAX_POINT_LIGHTS];
	SpotLight* spotLights[MAX_SPOT_LIGHTS];

	Skybox* skybox;

	Shader* directionalShadowShader;
	Shader* omniShadowShader;

	void OmniShadowLightPass(PointLight* light);

};

