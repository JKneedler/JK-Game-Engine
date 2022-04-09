#pragma once

#include <vector>

#include "Components/Transform.h"
#include "../../Enums.h"

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

	void AddChild(GameObject* child);

	bool NeedToDelete();

	Transform* transform;
	std::vector<GameObject*> children;
	GameObject* parent;

	~GameObject();

private:
	std::vector<BaseComponent*> components;
	bool toBeDeleted;
};

