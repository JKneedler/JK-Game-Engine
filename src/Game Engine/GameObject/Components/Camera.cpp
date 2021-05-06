#include "Camera.h"

Camera* Camera::mainCamera{ nullptr };

Camera:: Camera() : BaseComponent() { }

Camera::Camera(GLfloat startMoveSpeed, GLfloat startTurnSpeed, glm::mat4 startProjection) : BaseComponent() {
	projection = startProjection;

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

}

void Camera::Initialize() {
}

void Camera::Start() {
}

void Camera::Update() {
	
}

void Camera::Turn(GLfloat xChange, GLfloat yChange) {
	// Process Mouse movement
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	gameObject->transform->Rotate(-xChange, AXIS::WORLD_Y);
	gameObject->transform->Rotate(-yChange, AXIS::LOCAL_RIGHT);

	// Add Constraints
}

void Camera::MoveForwardBackward(float amt) {
	GLfloat velocity = moveSpeed * amt;
	gameObject->transform->Translate(AXIS::LOCAL_FORWARD, velocity);
}

void Camera::MoveRightLeft(float amt) {
	GLfloat velocity = moveSpeed * amt;
	gameObject->transform->Translate(AXIS::LOCAL_RIGHT, velocity);
}

glm::mat4 Camera::calculateViewMatrix() {
	position = gameObject->transform->getPosition();
	front = gameObject->transform->getForward();
	up = gameObject->transform->getUp();
	return glm::lookAt(position, position + front, up);
}

void Camera::SetUniforms(GLuint uniformProjection, GLuint uniformView, GLuint uniformEyePosition) {
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(calculateViewMatrix()));
	glUniform3f(uniformEyePosition, position.x, position.y, position.z);
}

Camera::~Camera() {

}
