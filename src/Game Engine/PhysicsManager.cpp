#include "PhysicsManager.h"

PhysicsManager::PhysicsManager() {
}

void PhysicsManager::AddCollider(Collider* newCollider) {
	ColliderData* colliderData = new ColliderData(newCollider);
	collidersData.push_back(colliderData);
}

void PhysicsManager::CheckForCollisions() {
	BroadCollisionCheck();
}

void PhysicsManager::RenderBBs() {
	for (auto colliderData : collidersData) {
		colliderData->collider->RenderBB();
	}
}

void PhysicsManager::BroadCollisionCheck() {
	for (auto colliderData : collidersData) {
		colliderData->UpdateRanges();
	}

	collidersData.sort(ColliderData::compareX);

	for (std::list<ColliderData*>::iterator data = collidersData.begin(); data != collidersData.end(); ++data) {
		ColliderData* colData = (ColliderData*)(*data);
		float start = colData->rangeX.x;

		RemovePassed(broadSearchStack, start, WORLD_X);

	}
}

void PhysicsManager::CreateBroadCheckList(AXIS axis) {
}

void PhysicsManager::RemovePassed(std::vector<ColliderData*> colliderStack, float point, AXIS axis) {
	for (auto collider : colliderStack) {
		if (axis == AXIS::WORLD_X) {
			for ()
		}
		else if (axis == AXIS::WORLD_Y) {

		}
		else {

		}
	}
}

PhysicsManager::~PhysicsManager() {
}