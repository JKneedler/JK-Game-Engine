#include "EngineManager.h"

EngineManager::EngineManager() {
}

void EngineManager::Initialize(GLint windowWidth, GLint windowHeight) {
	EngineManager* engine = getInstance();

	engine->window = new Window(windowWidth, windowHeight);
	engine->window->Initialize();

	engine->input = new Input(window->getWindow());
	engine->sceneManager = new SceneManager();
	engine->time = new Time();
	engine->physics = new PhysicsManager();

	engine->primitiveFactory = new PrimitiveFactory();

	testLine = new Line(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, -0.5));
}

Window* EngineManager::getWindowM() {
	return getInstance()->window;
}

Input* EngineManager::getInputM() {
	return getInstance()->input;
}

SceneManager* EngineManager::getSceneM() {
	return getInstance()->sceneManager;
}

Time* EngineManager::getTimeM() {
	return getInstance()->time;
}

Scene* EngineManager::getCurrentScene() {
	return getInstance()->sceneManager->getScene();
}

PhysicsManager* EngineManager::getPhysicsM() {
	return getInstance()->physics;
}

PrimitiveFactory* EngineManager::getPrimitiveF() {
	return getInstance()->primitiveFactory;
}

void EngineManager::Start() {
	EngineManager* engine = getInstance();

	engine->sceneManager->Initialize();
}

void EngineManager::Update() {
	EngineManager* engine = getInstance();

	engine->getTimeM()->UpdateDeltaTime();

	physics->CheckForCollisions();

	input->CycleKeys();
	glfwPollEvents();

	engine->sceneManager->Update();

	//Shadow Render
	engine->sceneManager->ShadowRender();

	//Real Render
	glViewport(0, 0, engine->getWindowM()->getBufferWidth(), engine->getWindowM()->getBufferHeight());
	engine->sceneManager->Render();

	physics->RenderBBs();

	//glm::mat4 transformMatrix = glm::mat4(1.0f);
	//transformMatrix = glm::translate(transformMatrix, glm::vec3(0, 0, 0));
	//transformMatrix = transformMatrix * glm::toMat4(glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
	//transformMatrix = glm::scale(transformMatrix, glm::vec3(1, 1, 1));
	//glm::mat4 mvp = Camera::mainCamera->getProjection() * Camera::mainCamera->calculateViewMatrix() * transformMatrix;
	//testLine->setMVP(mvp);
	//testLine->draw();

	glUseProgram(0);

	engine->getWindowM()->SwapBuffers();
}

EngineManager::~EngineManager() {
}
