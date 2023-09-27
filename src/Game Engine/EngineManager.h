#pragma once

#include "Window.h"
#include "Input.h"
#include "SceneManager.h"
#include "Time.h"
#include "PhysicsManager.h"
#include "Factories/PrimitiveFactory.h"
#include "Line.h"

class EngineManager {

public:
	EngineManager();

	//Change this to an inherited class
	static EngineManager* getInstance() {
		static EngineManager* instance = new EngineManager();
		return instance;
	}

	void Initialize(GLint windowWidth, GLint windowHeight);

	static Window* getWindowM();
	static Input* getInputM();
	static SceneManager* getSceneM();
	static Time* getTimeM();
	static Scene* getCurrentScene();
	static PhysicsManager* getPhysicsM();

	static PrimitiveFactory* getPrimitiveF();

	void Start();
	void Update();

	~EngineManager();

	Window* window;
	Input* input;
	SceneManager* sceneManager;
	Time* time;
	PhysicsManager* physics;
	
	PrimitiveFactory* primitiveFactory;

private:

	Line* testLine;
};

