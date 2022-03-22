#pragma once

#include <vector>
#include <string>

class Scene;

#include "GameObject/Components/MeshRenderer.h"
#include "Shader.h"
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
	void SetCamera(Camera* camera) { sceneCamera = camera; }

	void Initialize();
	void Update();
	void DirectionalShadowRender();
	void OmniShadowRender();
	void Render();

	DirectionalLight* getMainLight();
	PointLight** getPointLights();
	SpotLight** getSpotLights();
	unsigned int getPointLightCount();
	unsigned int getSpotLightCount();
	Camera* getSceneCamera() { return sceneCamera; }

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

	Camera* sceneCamera;

	void AddMesh(GameObject* newObj);
	void OmniShadowLightPass(PointLight* light);

};

