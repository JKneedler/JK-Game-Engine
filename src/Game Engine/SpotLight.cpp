#include "SpotLight.h"

SpotLight::SpotLight() : PointLight() {
	edge = 0.0f;
	procEdge = cosf(glm::radians(edge));
}

SpotLight::SpotLight(GLfloat shadowWidth, GLfloat shadowHeight,
						GLfloat red, GLfloat green, GLfloat blue, 
						GLfloat aIntensity, GLfloat dIntensity,
						GLfloat con, GLfloat lin, GLfloat exp, 
						GLfloat edg) : PointLight(shadowWidth, shadowHeight, red, green, blue, aIntensity, dIntensity, con, lin, exp) {
	edge = edg;
	procEdge = cosf(glm::radians(edge));
}

void SpotLight::Initialize() {
}

void SpotLight::Start() {
}

void SpotLight::Update() {
}

void SpotLight::Render() {
}

void SpotLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, 
							GLuint diffuseIntensityLocation, GLuint positionLocation, GLfloat directionLocation, 
							GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation, 
							GLfloat edgeLocation) {
	glm::vec3 position = GetGameObject()->transform->getPosition();
	glm::vec3 down = -(GetGameObject()->transform->getUp());
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);

	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(constantLocation, constant);
	glUniform1f(linearLocation, linear);
	glUniform1f(exponentLocation, exponent);

	glUniform3f(directionLocation, down.x, down.y, down.z);
	glUniform1f(edgeLocation, procEdge);
}

SpotLight::~SpotLight() {
}
