#include "PointLight.h"

PointLight::PointLight() : Light() {
	constant = 1.0f;
	linear = 0.0f;
	exponent = 0.0f;
}

PointLight::PointLight(GLfloat shadowWidth, GLfloat shadowHeight,
						GLfloat near, GLfloat far,
						GLfloat red, GLfloat green, GLfloat blue, 
						GLfloat aIntensity, GLfloat dIntensity, 
						GLfloat con, GLfloat lin, GLfloat exp) : Light(shadowWidth, shadowHeight, red, green, blue, aIntensity, dIntensity) {
	constant = con;
	linear = lin;
	exponent = exp;

	farPlane = far;

	float aspect = shadowWidth / shadowHeight;
	lightProj = glm::perspective(glm::radians(90.0f), aspect, near, far);

	shadowMap = new OmniShadowMap();
	shadowMap->Init(shadowWidth, shadowHeight);
}

void PointLight::Initialize() {
}

void PointLight::Start() {
}

void PointLight::Update() {
}

void PointLight::Render() {
}

void PointLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, 
							GLuint diffuseIntensityLocation, GLuint positionLocation, 
							GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation) {
	glm::vec3 position = GetGameObject()->transform->getPosition();
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);

	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(constantLocation, constant);
	glUniform1f(linearLocation, linear);
	glUniform1f(exponentLocation, exponent);
}

std::vector<glm::mat4> PointLight::CalculateLightTransform() {
	std::vector<glm::mat4> lightMatrices;
	glm::vec3 position = GetGameObject()->transform->getPosition();
	//+x, -x
	lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	//+y, -y
	lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
	//+z, -z
	lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

	return lightMatrices;
}

PointLight::~PointLight() {

}
