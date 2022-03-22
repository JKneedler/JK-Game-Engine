#include "SceneLoader.h"

SceneLoader::SceneLoader(AssetCache* assetCache) : assetCache(assetCache) {
	engine = EngineManager::getInstance();
}

// Change this to use the scenes_map.json file to generate the scenesMap
void SceneLoader::Initialize(const char* sceneMapLoc) {
	std::ifstream i(sceneMapLoc);
	json j;
	i >> j;
	for (auto it : j.items()) {
		std::string sceneFileLoc = it.value();
		std::cout << sceneFileLoc << std::endl;
		std::ifstream k(sceneFileLoc);
		json sceneJson;
		k >> sceneJson;
		sceneMap.insert({ it.key().c_str(), sceneJson.dump() });
	}
}

Scene* SceneLoader::LoadScene(std::string sceneName) {
	std::map<std::string, std::string>::iterator it = sceneMap.find(sceneName);
	json j;
	Scene* scene = new Scene();

	// Add exception handling here to catch a parsing error and print it back out the console
	if (it != sceneMap.end()) {
		j = json::parse(it->second);

		// Shadow Shaders
		std::string directionalSSName = j["DirectionalShadowShader"].get<std::string>();
		Shader* directionalSS = assetCache->LoadShader(directionalSSName.c_str());
		scene->SetDirectionalShadowShader(directionalSS);

		std::string omniDirectionalSSName = j["OmniDirectionalShadowShader"].get<std::string>();
		Shader* omniDirectionalSS = assetCache->LoadShader(omniDirectionalSSName.c_str());
		scene->SetOmniShadowShader(omniDirectionalSS);

		CreateCamera(j["Camera"], *scene);
		CreateDirectionalLight(j["Lights"]["DirectionalLight"], *scene);
		CreatePointLights(j["Lights"]["PointLights"], *scene);
		CreateSpotLights(j["Lights"]["SpotLights"], *scene);
		CreateSkybox(j["Skybox"], *scene);
		CreateGameObjects(j["GameObjects"], *scene);
		
	}
	else {
		std::cout << "Scene Map found no result for sceneName  {" << sceneName << "} : No scene loaded" << std::endl;
	}

	return scene;
}

void SceneLoader::CreateCamera(json cameraJson, Scene& scene) {
	glm::mat4 projection = glm::perspective(glm::radians(cameraJson["FieldOfViewY"].get<GLfloat>()), (GLfloat)engine->getWindowM()->getBufferWidth() / (GLfloat)engine->getWindowM()->getBufferHeight(), cameraJson["Near"].get<GLfloat>(), cameraJson["Far"].get<GLfloat>());
	Camera* camera = new Camera(cameraJson["StartMoveSpeed"], cameraJson["StartTurnSpeed"], projection);
	scene.SetCamera(camera);

	GameObject* cameraObj = new GameObject(camera);
	scene.AddGameObject(cameraObj);
}

void SceneLoader::CreateDirectionalLight(json dLJson, Scene& scene) {
	DirectionalLight* directionalLightComp = new DirectionalLight(
		dLJson["ShadowWidth"],
		dLJson["ShadowHeight"],
		dLJson["Red"],
		dLJson["Green"],
		dLJson["Blue"],
		dLJson["AmbientIntensity"],
		dLJson["DirectionalIntensity"]
	);
	GameObject* directionalLight = new GameObject(directionalLightComp);
	std::vector<GLfloat> startPosition = dLJson["Position"];
	std::vector<GLfloat> startRotation = dLJson["Rotation"];

	directionalLight->transform->SetPosition(glm::vec3(startPosition[0], startPosition[1], startPosition[2]));
	directionalLight->transform->Rotate(startRotation[0], AXIS::WORLD_X);
	directionalLight->transform->Rotate(startRotation[1], AXIS::WORLD_Y);
	directionalLight->transform->Rotate(startRotation[2], AXIS::WORLD_Z);

	scene.AddDirectionalLight(directionalLightComp);
	scene.AddGameObject(directionalLight);
}

void SceneLoader::CreatePointLights(json pLJson, Scene& scene) {
	for (auto it : pLJson.items()) {
		json pLJ = it.value();

		PointLight* pointLightComp = new PointLight(
			pLJ["ShadowWidth"],
			pLJ["ShadowHeight"],
			pLJ["Near"],
			pLJ["Far"],
			pLJ["Red"],
			pLJ["Green"],
			pLJ["Blue"],
			pLJ["AmbientIntensity"],
			pLJ["DirectionalIntensity"],
			pLJ["Constant"],
			pLJ["Linear"],
			pLJ["Exponent"]
		);
		GameObject* pointLight = new GameObject(pointLightComp);
		std::vector<GLfloat> startPosition = pLJ["Position"];
		std::vector<GLfloat> startRotation = pLJ["Rotation"];

		pointLight->transform->SetPosition(glm::vec3(startPosition[0], startPosition[1], startPosition[2]));
		pointLight->transform->Rotate(startRotation[0], AXIS::WORLD_X);
		pointLight->transform->Rotate(startRotation[1], AXIS::WORLD_Y);
		pointLight->transform->Rotate(startRotation[2], AXIS::WORLD_Z);

		scene.AddPointLight(pointLightComp);
		scene.AddGameObject(pointLight);
	}
}

void SceneLoader::CreateSpotLights(json sLJson, Scene& scene) {
	for (auto it : sLJson.items()) {
		json sLJ = it.value();

		SpotLight* spotLightComp = new SpotLight(
			sLJ["ShadowWidth"],
			sLJ["ShadowHeight"],
			sLJ["Near"],
			sLJ["Far"],
			sLJ["Red"],
			sLJ["Green"],
			sLJ["Blue"],
			sLJ["AmbientIntensity"],
			sLJ["DirectionalIntensity"],
			sLJ["Constant"],
			sLJ["Linear"],
			sLJ["Exponent"],
			sLJ["Edge"]
		);
		GameObject* spotLight = new GameObject(spotLightComp);
		std::vector<GLfloat> startPosition = sLJ["Position"];
		std::vector<GLfloat> startRotation = sLJ["Rotation"];

		spotLight->transform->SetPosition(glm::vec3(startPosition[0], startPosition[1], startPosition[2]));
		spotLight->transform->Rotate(startRotation[0], AXIS::WORLD_X);
		spotLight->transform->Rotate(startRotation[1], AXIS::WORLD_Y);
		spotLight->transform->Rotate(startRotation[2], AXIS::WORLD_Z);

		scene.AddPointLight(spotLightComp);
		scene.AddGameObject(spotLight);
	}
}

void SceneLoader::CreateSkybox(json skyboxJson, Scene& scene) {
	std::vector<std::string> skyboxFaces = skyboxJson["SkyboxFaces"];

	Shader* skyShader = assetCache->LoadShader("Skybox");
	Skybox* skybox = new Skybox(skyShader, skyboxFaces);
	scene.SetSkybox(skybox);
}

void SceneLoader::CreateGameObjects(json gameObjectsJson, Scene& scene) {
	for (auto it : gameObjectsJson.items()) {
		GameObject* gameObject = CreateGameObject(it.value());
		scene.AddGameObject(gameObject);
	}
}

GameObject* SceneLoader::CreateGameObject(json gameObjectJson) {
	GameObject* gameObject = nullptr;
	if (gameObjectJson["Mesh"]["Primitive"] != "") {
		gameObject = CreatePrimitiveGameObject(gameObjectJson);
	}
	else if (gameObjectJson["Mesh"]["Model"] != "") {
		// Add model support
	}
	else {
		// Fill in a default
	}

	for (auto it : gameObjectJson["Children"].items()) {
		GameObject* child = CreateGameObject(it.value());
		gameObject->AddChild(child);
	}

	return gameObject;
}

GameObject* SceneLoader::CreatePrimitiveGameObject(json gameObjectJson) {
	int primitiveNum = std::stoi(gameObjectJson["Mesh"]["Primitive"].get<std::string>());
	Mesh* mesh = engine->getPrimitiveF()->CreatePrimitive(static_cast<PRIMITIVES>(primitiveNum));

	Material* material = GetMaterial(gameObjectJson["Material"]);
	MeshRenderer* renderer = new MeshRenderer(mesh, material);
	GameObject* gameObject = new GameObject(renderer);

	std::vector<GLfloat> startPosition = gameObjectJson["Position"];
	std::vector<GLfloat> startRotation = gameObjectJson["Rotation"];
	std::vector<GLfloat> startScale = gameObjectJson["Scale"];

	gameObject->transform->SetPosition(glm::vec3(startPosition[0], startPosition[1], startPosition[2]));
	gameObject->transform->Rotate(startRotation[0], AXIS::WORLD_X);
	gameObject->transform->Rotate(startRotation[1], AXIS::WORLD_Y);
	gameObject->transform->Rotate(startRotation[2], AXIS::WORLD_Z);
	gameObject->transform->SetScale(glm::vec3(startScale[0], startScale[1], startScale[2]));

	return gameObject;
}

Material* SceneLoader::GetMaterial(json materialJson) {
	Shader* shader = assetCache->LoadShader(materialJson["Shader"].get<std::string>().c_str());
	Texture* texture = assetCache->LoadTexture(materialJson["Texture"].get<std::string>().c_str());
	GLfloat specularIntensity = materialJson["Specular_Intensity"].get<GLfloat>();
	GLfloat shine = materialJson["Shine"].get<GLfloat>();
	return new Material(shader, texture, specularIntensity, shine);
}
