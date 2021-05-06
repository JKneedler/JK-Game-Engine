#include "PointLight.h"

PointLight::PointLight() : Light() {
	constant = 1.0f;
	linear = 0.0f;
	exponent = 0.0f;
}

PointLight::PointLight(GLfloat shadowWidth, GLfloat shadowHeight,
						GLfloat red, GLfloat green, GLfloat blue, 
						GLfloat aIntensity, GLfloat dIntensity, 
						GLfloat con, GLfloat lin, GLfloat exp) : Light(shadowWidth, shadowHeight, red, green, blue, aIntensity, dIntensity) {
	constant = con;
	linear = lin;
	exponent = exp;
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

PointLight::~PointLight() {

}
