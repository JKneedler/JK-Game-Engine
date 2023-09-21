#include "Transform.h"
#include <iostream>

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
	model = GetTransformMatrix();

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
}

glm::mat4 Transform::GetTransformMatrix() {
	glm::mat4 transformMatrix = glm::mat4(1.0f);
	transformMatrix = glm::translate(transformMatrix, position);
	transformMatrix = transformMatrix * glm::toMat4(rotation);
	transformMatrix = glm::scale(transformMatrix, scale);

	if (parent != nullptr) {
		glm::mat4 parentMatrix = parent->GetTransformMatrix();
		transformMatrix = parentMatrix * transformMatrix;
	}

	return transformMatrix;
}

void Transform::AddChild(Transform* newChild) {
	children.push_back(newChild);
	newChild->SetParent(this);
}

Transform* Transform::RemoveChild(unsigned int childNum) {
	Transform* childRemoved = nullptr;
	if (children.size() >= childNum) {
		childRemoved = children[childNum];
		childRemoved->DetachFromParent();

		children.erase(children.begin()+childNum);
	}

	return childRemoved;
}

void Transform::RemoveChildren() {
	for (auto child : children) {
		child->DetachFromParent();
	}

	children.clear();
}

void Transform::DetachFromParent() {
	glm::vec3 skew = glm::vec3(1.0f);
	glm::vec4 perspective = glm::vec4(1.0f);
	
	glm::mat4 matrix = GetTransformMatrix();
	glm::decompose(matrix, scale, rotation, position, skew, perspective);

	parent = nullptr;
}

// TODO : Need to figure out how these manipulations work for the children
//			Specifically how the hell does scale work
//			Rotation should work by rotating around the axis located at the origin
//			LOOK UP COMBINED TRANSFORMATION MATRIX
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

void Transform::SetParent(Transform* newParent) {
	glm::mat4 matrix = GetTransformMatrix();
	glm::mat4 newParentMatrix = newParent->GetTransformMatrix();

	glm::mat4 relativeMatrix = glm::inverse(newParentMatrix) * matrix;

	glm::vec3 skew = glm::vec3(1.0f);
	glm::vec4 perspective = glm::vec4(1.0f);

	glm::decompose(relativeMatrix, scale, rotation, position, skew, perspective);

	parent = newParent;
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