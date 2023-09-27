#pragma once

#include <list>
#include <vector>
#include <iostream>

#include "GameObject/Components/Collider.h";

class ColliderData {
public:
	Collider* collider;
	glm::vec2 rangeX;
	glm::vec2 rangeY;
	glm::vec2 rangeZ;

	ColliderData(Collider* collider) {
		this->collider = collider;
		UpdateRanges();
	};

	void UpdateRanges() {
		collider->UpdateRanges();
		rangeX = collider->GetRange(AXIS::WORLD_X);
		rangeY = collider->GetRange(AXIS::WORLD_Y);
		rangeZ = collider->GetRange(AXIS::WORLD_Z);
	};

	static bool compareX(ColliderData* first, ColliderData* second) {
		return first->rangeX.x < second->rangeX.x;
	}
};

class PossibleCollision {
	ColliderData* col1;
	ColliderData* col2;

	PossibleCollision(ColliderData* col1, ColliderData* col2) {
		this->col1 = col1;
		this->col2 = col2;
	}
};

class PhysicsManager {
public:
	PhysicsManager();

	void AddCollider(Collider* newCollider);

	void CheckForCollisions();

	void RenderBBs();

	~PhysicsManager();
private:

	void BroadCollisionCheck();
	void CreateBroadCheckList(AXIS axis);

	void RemovePassed(std::vector<ColliderData*> colliderStack, float point, AXIS axis);

	std::list<ColliderData*> collidersData;
	std::vector<ColliderData*> colliderListY;
	std::vector<ColliderData*> colliderListZ;

	std::vector<ColliderData*> broadSearchStack;

	std::vector<PossibleCollision*> possibleCollisions;

};