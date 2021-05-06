#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#include "../BaseComponent.h"
#include "../GameObject.h"

class Camera :
	public BaseComponent {

public:
	Camera();
	Camera(GLfloat startMoveSpeed, GLfloat startTurnSpeed, glm::mat4 startProjection);

	void Initialize();
	void Start();

	void Update();

	//Temporary methods
	void Turn(GLfloat xChange, GLfloat yChange);
	void MoveForwardBackward(float amt);
	void MoveRightLeft(float amt);

	TYPES GetType() { return CAMERA; };

	static Camera* mainCamera;

	glm::mat4 calculateViewMatrix();

	void SetUniforms(GLuint uniformProjection, GLuint uniformView, GLuint uniformEyePosition);

	~Camera();

private:
	glm::mat4 projection;
	glm::vec3 position, front, up;

	GLfloat moveSpeed, turnSpeed;

};

