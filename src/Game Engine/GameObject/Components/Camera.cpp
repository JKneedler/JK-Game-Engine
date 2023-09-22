#include "Camera.h"

Camera* Camera::mainCamera{ nullptr };

Camera:: Camera() : BaseComponent() { }

Camera::Camera(glm::mat4 startProjection) : BaseComponent() {
	projection = startProjection;

}

void Camera::Initialize() {
}

void Camera::Start() {
}

void Camera::Update() {
	
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
