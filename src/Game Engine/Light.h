#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Objects/GameObject/GameObject.h"
#include "ShadowMap.h"

class Light : 
	public BaseComponent {
public:
	Light();
	Light(GLfloat shadowWidth, GLfloat shadowHeight, GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity);

	void Initialize();
	void Start();

	void Update();
	void Render();

	ShadowMap* GetShadowMap() { return shadowMap; }

	TYPES GetType() { return LIGHT; };

	~Light();

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;

	glm::mat4 lightProj;

	ShadowMap* shadowMap;
};

