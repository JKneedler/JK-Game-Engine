#pragma once

#include <vector>

#include "Components/Transform.h"
#include "../Enums.h"

class GameObject {
	
public:
	GameObject();
	GameObject(BaseComponent* component);
	GameObject(std::vector<BaseComponent*> myComponents);

	void Initialize();
	void Start();

	void Update();
	void Render();

	void AddComponent(BaseComponent* component);

	bool HasComponent(TYPES type);
	void* GetComponent(TYPES type);

	Transform* transform;

	~GameObject();

private:
	std::vector<GameObject*> children;
	std::vector<BaseComponent*> components;
};

