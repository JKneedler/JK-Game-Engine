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

	engine->primitiveFactory = new PrimitiveFactory();
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

	glfwPollEvents();

	ImGui::Render();

	engine->sceneManager->Update();

	//Shadow Render
	engine->sceneManager->ShadowRender();

	//Real Render
	glViewport(0, 0, engine->getWindowM()->getBufferWidth(), engine->getWindowM()->getBufferHeight());
	engine->sceneManager->Render();

	glUseProgram(0);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	engine->getWindowM()->SwapBuffers();
}

EngineManager::~EngineManager() {
}
