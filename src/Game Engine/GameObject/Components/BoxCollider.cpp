#include "BoxCollider.h"

BoxCollider::BoxCollider() {
	
}

BoxCollider::BoxCollider(glm::vec3 origin, glm::vec3 size) {
	for (int i = 0; i < 8; i++) {
		verts[i] = glm::vec3();
	}
	position = origin;
	scale = size;
}

void BoxCollider::UpdateRanges() {
	//glm::mat4 objectMatrix = gameObject->transform->GetTransformMatrix();
	//if (!glm::equal(objectMatrix, prevObjectMatrix).b) {
		// change container to just use position and scale. Make the origin point be the position with a transformation matrix.

		// Get Transformation matrix from variables position/scale + 1,0,0,0 quaternion rotation
		glm::quat noRotate = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		glm::mat4 transformMatrix = glm::mat4(1.0f);
		transformMatrix = glm::translate(transformMatrix, position);
		transformMatrix = transformMatrix * glm::toMat4(noRotate);
		transformMatrix = glm::scale(transformMatrix, scale);

		// Multiply by object matrix to get world position matrix
		glm::mat4 objectMatrix = gameObject->transform->GetTransformMatrix();
		transformMatrix = objectMatrix * transformMatrix;

		// decompose to get world position, rotation, scale
		glm::vec3 worldPos = glm::vec3(0.0f);
		glm::quat worldRot = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		glm::vec3 worldScale = glm::vec3(1.0f);
		glm::vec3 skew = glm::vec3(1.0f);
		glm::vec4 perspective = glm::vec4(1.0f);

		glm::decompose(transformMatrix, worldScale, worldRot, worldPos, skew, perspective);

		// use 1,0,0 for x, 0,1,0 for y, 0,0,1 for z and rotate those values by the world quaternion in order to get forward, right, and up vectors
		glm::vec3 forward = glm::normalize(glm::rotate(worldRot, glm::vec3(0.0f, 0.0f, 1.0f)));
		glm::vec3 right = glm::normalize(glm::rotate(worldRot, glm::vec3(1.0f, 0.0f, 0.0f)));
		glm::vec3 up = glm::normalize(glm::cross(forward, right));

		// use those vectors to get the vertice locations
		glm::vec3 rightWall = (right * (worldScale.x / 2));
		glm::vec3 leftWall = (right * -(worldScale.x / 2));
		glm::vec3 topWall = (up * (worldScale.y / 2));
		glm::vec3 bottomWall = (up * -(worldScale.y / 2));
		glm::vec3 frontWall = (forward * (worldScale.z / 2));
		glm::vec3 backWall = (forward * -(worldScale.z / 2));

		verts[0] = worldPos + (rightWall + bottomWall + backWall);
		verts[1] = worldPos + (leftWall + bottomWall + backWall);
		verts[2] = worldPos + (rightWall + bottomWall + frontWall);
		verts[3] = worldPos + (leftWall + bottomWall + frontWall);
		verts[4] = worldPos + (rightWall + topWall + backWall);
		verts[5] = worldPos + (leftWall + topWall + backWall);
		verts[6] = worldPos + (rightWall + topWall + frontWall);
		verts[7] = worldPos + (leftWall + topWall + frontWall);

		SetRanges();
//	}

	//prevObjectMatrix = objectMatrix;
}

void BoxCollider::SetRanges() {
	rangeX = glm::vec2(verts[0].x, verts[0].x);
	rangeY = glm::vec2(verts[0].y, verts[0].y);
	rangeZ = glm::vec2(verts[0].z, verts[0].z);

	for (int i = 0; i < 8; i++) {
		glm::vec3 vert = verts[i];

		if (vert.x < rangeX.x) rangeX.x = vert.x;
		if (vert.x > rangeX.y) rangeX.y = vert.x;
		if (vert.y < rangeY.x) rangeY.x = vert.y;
		if (vert.y > rangeY.y) rangeY.y = vert.y;
		if (vert.z < rangeZ.x) rangeZ.x = vert.z;
		if (vert.z > rangeZ.y) rangeZ.y = vert.z;
	}
}

glm::vec2 BoxCollider::GetRange(AXIS axis) {
	if (axis == AXIS::WORLD_X) return rangeX;
	if (axis == AXIS::WORLD_Y) return rangeY;
	if (axis == AXIS::WORLD_Z) return rangeZ;

	return rangeX;
}

void BoxCollider::CreateBBLines() {
	lines.clear();

	Line* line1t2 = new Line(verts[0], verts[1]);
	Line* line2t4 = new Line(verts[1], verts[3]);
	Line* line4t3 = new Line(verts[3], verts[2]);
	Line* line3t1 = new Line(verts[2], verts[0]);
	Line* line5t6 = new Line(verts[4], verts[5]);
	Line* line6t8 = new Line(verts[5], verts[7]);
	Line* line8t7 = new Line(verts[7], verts[6]);
	Line* line7t5 = new Line(verts[6], verts[4]);
	Line* line1t5 = new Line(verts[0], verts[4]);
	Line* line2t6 = new Line(verts[1], verts[5]);
	Line* line4t8 = new Line(verts[3], verts[7]);
	Line* line3t7 = new Line(verts[2], verts[6]);

	lines.push_back(line1t2);
	lines.push_back(line2t4);
	lines.push_back(line4t3);
	lines.push_back(line3t1);
	lines.push_back(line5t6);
	lines.push_back(line6t8);
	lines.push_back(line8t7);
	lines.push_back(line7t5);
	lines.push_back(line1t5);
	lines.push_back(line2t6);
	lines.push_back(line4t8);
	lines.push_back(line3t7);
}

void BoxCollider::RenderBB() {
	CreateBBLines();
	for (auto line : lines) {
		glm::mat4 transformMatrix = glm::mat4(1.0f);
		transformMatrix = glm::translate(transformMatrix, glm::vec3(0, 0, 0));
		transformMatrix = transformMatrix * glm::toMat4(glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
		transformMatrix = glm::scale(transformMatrix, glm::vec3(1, 1, 1));
		glm::mat4 mvp = Camera::mainCamera->getProjection() * Camera::mainCamera->calculateViewMatrix() * transformMatrix;

		line->setMVP(mvp);
		line->draw();
	}
}

void BoxCollider::PrintVec3(const char* name, glm::vec3 vector) {
	std::cout << name << ": ( " << vector.x << ", " << vector.y << ", " << vector.z << ")" << std::endl;
}

void BoxCollider::PrintVerts() {
	std::cout << "verts[0] : ( " << verts[0].x << ", " << verts[0].y << ", " << verts[0].z << ")" << std::endl;
	std::cout << "verts[1] : ( " << verts[1].x << ", " << verts[1].y << ", " << verts[1].z << ")" << std::endl;
	std::cout << "verts[2] : ( " << verts[2].x << ", " << verts[2].y << ", " << verts[2].z << ")" << std::endl;
	std::cout << "verts[3] : ( " << verts[3].x << ", " << verts[3].y << ", " << verts[3].z << ")" << std::endl;
	std::cout << "verts[4] : ( " << verts[4].x << ", " << verts[4].y << ", " << verts[4].z << ")" << std::endl;
	std::cout << "verts[5] : ( " << verts[5].x << ", " << verts[5].y << ", " << verts[5].z << ")" << std::endl;
	std::cout << "verts[6] : ( " << verts[6].x << ", " << verts[6].y << ", " << verts[6].z << ")" << std::endl;
	std::cout << "verts[7] : ( " << verts[7].x << ", " << verts[7].y << ", " << verts[7].z << ")" << std::endl;
}

BoxCollider::~BoxCollider() {
}
