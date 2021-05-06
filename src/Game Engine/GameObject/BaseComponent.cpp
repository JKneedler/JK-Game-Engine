#include "BaseComponent.h"

BaseComponent::BaseComponent() {
}

void BaseComponent::Initialize() {}

void BaseComponent::Start() {}

void BaseComponent::Update() {}

void BaseComponent::Render() {}

void BaseComponent::Render(Shader* shader) {
}

TYPES BaseComponent::GetType() {
	return BASE_COMPONENT;
}

BaseComponent::~BaseComponent() {}
