#pragma once

#include <map>
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <GL/glew.h>

#include "AssetCache.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"
#include "Scene.h"
#include "json.hpp"

using json = nlohmann::json;

class SceneLoader {
public:
	SceneLoader(AssetCache* assetCache);

	void Initialize(const char* sceneDirectory);

	Scene* LoadScene(std::string sceneName);

private:
	EngineManager* engine;
	AssetCache* assetCache;
	std::map<std::string, std::string> sceneMap;

	void CreateCamera(json cameraJson, Scene& scene);

	void CreateDirectionalLight(json dLJson, Scene &scene);
	void CreatePointLights(json pLJson, Scene& scene);
	void CreateSpotLights(json sLJson, Scene& scene);

	void CreateSkybox(json skyboxJson, Scene& scene);

	void CreateGameObjects(json gameObjectsJson, Scene& scene);
	GameObject* CreateGameObject(json gameObjectsJson);
	GameObject* CreatePrimitiveGameObject(json gameObjectJson);
	Material* GetMaterial(json materialJson);
};

