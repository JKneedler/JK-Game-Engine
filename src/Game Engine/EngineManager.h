#pragma once

#include "Window.h"
#include "Input.h"
#include "SceneManager.h"
#include "Time.h"
#include "Factories/PrimitiveFactory.h"

class EngineManager {

public:
	EngineManager();

	static EngineManager* getInstance() {
		static EngineManager* instance = new EngineManager();
		return instance;
	}

	void Initialize(GLint windowWidth, GLint windowHeight);

	static Window* getWindowM();
	static Input* getInputM();
	static SceneManager* getSceneM();
	static Time* getTimeM();

	static PrimitiveFactory* getPrimitiveF();

	void Start();
	void Update();

	~EngineManager();

	Window* window;
	Input* input;
	SceneManager* sceneManager;
	Time* time;
	
	PrimitiveFactory* primitiveFactory;

private:
};

