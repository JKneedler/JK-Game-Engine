#pragma once

#include <vector>

#include "Components/Transform.h"
#include "../Enums.h"

class Shader;

class GameObject {
	
public:
	GameObject();
	GameObject(BaseComponent* component);
	GameObject(std::vector<BaseComponent*> myComponents);

	void Initialize();
	void Start();

	void Update();
	void Render();
	void Render(Shader* shader);

	void AddComponent(BaseComponent* component);
	bool HasComponent(TYPES type);
	void* GetComponent(TYPES type);

	bool NeedToDelete();

	Transform* transform;

	~GameObject();

private:
	std::vector<BaseComponent*> components;
	bool toBeDeleted;
};

