#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light() {
	lightProj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}

DirectionalLight::DirectionalLight(GLfloat shadowWidth, GLfloat shadowHeight,
									GLfloat red, GLfloat green, GLfloat blue, 
									GLfloat aIntensity, GLfloat dIntensity) : Light(shadowWidth, shadowHeight, red, green, blue, aIntensity, dIntensity) {
	lightProj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}

void DirectionalLight::Initialize() {
}

void DirectionalLight::Start() {
}

void DirectionalLight::Update() {
}

void DirectionalLight::Render() {
}

void DirectionalLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation,
	GLuint diffuseIntensityLocation, GLuint directionLocation) {
	glm::vec3 direction = -(GetGameObject()->transform->getUp());
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}

glm::mat4 DirectionalLight::CalculateLightTransform() {
	glm::vec3 direction = -(GetGameObject()->transform->getUp());
	if (direction == glm::vec3(0.0f, 1.0f, 0.0f) || direction == glm::vec3(0.0f, -1.0f, 0.0f)) {
		return lightProj * glm::lookAt(-direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	}
	return lightProj * glm::lookAt(-direction * 20.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

DirectionalLight::~DirectionalLight() {

}
