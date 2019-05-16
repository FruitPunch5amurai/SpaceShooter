#pragma once
//EntityX
#include <EntityX/entityx.h>
#include <iostream>
#include "IAI.h"

struct AI_HomingProjectile: public IAi
{
	AI_HomingProjectile(entityx::Entity t):
	target(t)
	{
	}
	~AI_HomingProjectile()
	{

	}
	void Update(entityx::Entity self, entityx::EventManager &events, entityx::TimeDelta dt) override {

		auto position = self.component<TransformComponent>();
		auto physics = self.component<PhysicsComponent>();

		auto targetPosition = target.component<TransformComponent>();

		glm::vec2 toTarget = targetPosition->position - position->position;
		toTarget /= glm::length(toTarget);
		glm::vec2 velocity = toTarget * physics->maxSpeed;
		physics->currentSpeed = velocity;
	}

	entityx::Entity target;
};