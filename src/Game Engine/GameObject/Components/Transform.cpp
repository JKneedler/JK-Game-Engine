#include "Transform.h"

Transform::Transform() : BaseComponent() {
	position = glm::vec3(0.0f);
	rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f);
	model = glm::mat4(1.0f);

	forward = glm::vec3(0.0f, 0.0f, 1.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

Transform::Transform(glm::vec3 startPos) : BaseComponent() {
	position = glm::vec3(startPos.x, startPos.y, startPos.z);
	rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f);
	model = glm::mat4(1.0f);

	forward = glm::vec3(0.0f, 0.0f, 1.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

Transform::Transform(glm::vec3 startPos, glm::vec3 startScale) : BaseComponent() {
	position = glm::vec3(startPos.x, startPos.y, startPos.z);
	rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	scale = glm::vec3(startScale.x, startScale.y, startScale.z);
	model = glm::mat4(1.0f);

	forward = glm::vec3(0.0f, 0.0f, 1.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

Transform::Transform(glm::vec3 startPos, glm::quat startRot, glm::vec3 startScale) : BaseComponent() {
	position = glm::vec3(startPos.x, startPos.y, startPos.z);
	rotation = glm::quat(startRot.x, startRot.y, startRot.z, startRot.w);
	scale = glm::vec3(startScale.x, startScale.y, startScale.z);
	model = glm::mat4(1.0f);

	forward = glm::vec3(0.0f, 0.0f, 1.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Transform::Initialize() {
}

void Transform::Start() {
}

void Transform::Update() {
}

void Transform::SetModel(GLuint uniformModel) {
	model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = model * glm::toMat4(rotation);
	model = glm::scale(model, scale);

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
}

void Transform::SetPosition(glm::vec3 newPos) {
	position.x = newPos.x;
	position.y = newPos.y;
	position.z = newPos.z;
}

void Transform::SetScale(glm::vec3 newScale) {
	scale.x = newScale.x;
	scale.y = newScale.y;
	scale.z = newScale.z;
}

void Transform::SetRotation(glm::quat newRot) {
	rotation.x = newRot.x;
	rotation.y = newRot.y;
	rotation.z = newRot.z;
	rotation.w = newRot.w;
}

void Transform::Translate(glm::vec3 translation) {
	position.x += translation.x;
	position.y += translation.y;
	position.z += translation.z;
}

void Transform::Translate(AXIS axis, float distance) {
	glm::vec3 translation = GetAxisVector(axis) * distance;
	Translate(translation);
}

void Transform::Rotate(float angle, AXIS axis) {
	glm::vec3 rotVector = GetAxisVector(axis);
	glm::quat rotQuat = glm::angleAxis(glm::radians(angle), rotVector);
	rotation = rotQuat * rotation;

	forward = glm::normalize(glm::rotate(rotQuat, forward));
	right = glm::normalize(glm::rotate(rotQuat, right));
	up = glm::normalize(glm::cross(forward, right));
}

glm::vec3 Transform::GetAxisVector(AXIS axis) {
	switch (axis) {
		case WORLD_X:
			return glm::vec3(1.0f, 0.0f, 0.0f);
		case WORLD_Y:
			return glm::vec3(0.0f, 1.0f, 0.0f);
		case WORLD_Z:
			return glm::vec3(0.0f, 0.0f, 1.0f);
		case LOCAL_FORWARD:
			return forward;
		case LOCAL_RIGHT:
			return right;
		case LOCAL_UP:
			return up;
		default:
			return glm::vec3(0.0f, 0.0f, 0.0f);
	}
}

void Transform::PrintDirections() {
	glm::vec3 eulerAng = glm::eulerAngles(rotation);
	printf("Angles: (%f, %f, %f)\n", glm::degrees(eulerAng.x), glm::degrees(eulerAng.y), glm::degrees(eulerAng.z));
	printf("Forward: (%f, %f, %f)\n", forward.x, forward.y, forward.z);
	printf("Right: (%f, %f, %f)\n", right.x, right.y, right.z);
	printf("Up: (%f, %f, %f)\n", up.x, up.y, up.z);
	glm::vec3 down = -up;
	printf("Down: (%f, %f, %f)\n", down.x, down.y, down.z);
}

Transform::~Transform() {
}