#pragma once

#include "../../Enums.h"

class Shader;
class GameObject;

class BaseComponent {

public:
	BaseComponent();

	virtual void Initialize();
	virtual void Start();

	virtual void Update();
	virtual void Render();
	virtual void Render(Shader* shader);

	virtual TYPES GetType();

	GameObject* GetGameObject() { return gameObject; }
	void SetGameObject(GameObject* myGameObject) { gameObject = myGameObject; };

	virtual ~BaseComponent();

protected:
	GameObject* gameObject;

};
