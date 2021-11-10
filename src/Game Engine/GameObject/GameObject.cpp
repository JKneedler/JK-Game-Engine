#include "GameObject.h"

GameObject::GameObject() {
	transform = new Transform();
	transform->SetGameObject(this);
	components = std::vector<BaseComponent*>();
}

GameObject::GameObject(BaseComponent* component) {
	transform = new Transform();
	transform->SetGameObject(this);
	component->SetGameObject(this);
	components = std::vector<BaseComponent*>({ component });
}

GameObject::GameObject(std::vector<BaseComponent*> myComponents) {
	transform = new Transform();
	transform->SetGameObject(this);
	for (size_t i = 0; i < myComponents.size(); i++) { myComponents[i]->SetGameObject(this); }
	components = std::vector<BaseComponent*>(myComponents);
}

void GameObject::Initialize() {
	transform->Initialize();
	for (size_t i = 0; i < components.size(); i++) {
		components[i]->Initialize();
	}
	for (size_t i = 0; i < children.size(); i++) {
		children[i]->Initialize();
	}
}

void GameObject::Start() {
	transform->Start();
	for (size_t i = 0; i < components.size(); i++) {
		components[i]->Start();
	}
	for (size_t i = 0; i < children.size(); i++) {
		children[i]->Start();
	}
}

void GameObject::Update() {
	transform->Update();
	for (size_t i = 0; i < components.size(); i++) {
		components[i]->Update();
	}
	for (size_t i = 0; i < children.size(); i++) {
		children[i]->Update();
	}
}

void GameObject::Render() {
	for (size_t i = 0; i < components.size(); i++) {
		components[i]->Render();
	}
	for (size_t i = 0; i < children.size(); i++) {
		children[i]->Render();
	}
}

void GameObject::Render(Shader* shader) {
	for (size_t i = 0; i < components.size(); i++) {
		components[i]->Render(shader);
	}
	for (size_t i = 0; i < children.size(); i++) {
		children[i]->Render(shader);
	}
}

void GameObject::AddComponent(BaseComponent* component) {
	component->SetGameObject(this);
	components.push_back(component);
}

bool GameObject::HasComponent(TYPES type) {
	for (size_t i = 0; i < components.size(); i++) {
		if (components[i]->GetType() == type) {
			return true;
		}
	}
	return false;
}

void* GameObject::GetComponent(TYPES type) {
	for (size_t i = 0; i < components.size(); i++) {
		if (components[i]->GetType() == type) {
			return components[i];
		}
	}
	return nullptr;
}

GameObject::~GameObject() {
}
