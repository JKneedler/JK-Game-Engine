#include "Material.h"

Material::Material() {
	specularIntensity = 0.0f;
	shininess = 0.0f;
}

Material::Material(GLfloat sIntensity, GLfloat shine) {
	specularIntensity = sIntensity;
	shininess = shine;
}

Material::Material(Shader* myShader, Texture* myTexture, GLfloat sIntensity, GLfloat shine) {
	shader = myShader;
	texture = myTexture;
	specularIntensity = sIntensity;
	shininess = shine;
}

void Material::UseMaterial() {
	glUniform1f(shader->GetSpecularIntensityLocation(), specularIntensity);
	glUniform1f(shader->GetShininessLocation(), shininess);
	texture->UseTexture();
}

void Material::UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation) {
	glUniform1f(specularIntensityLocation, specularIntensity);
	glUniform1f(shininessLocation, shininess);
}

Material::~Material() {

}
