#pragma once
//EntityX
#include <EntityX/entityx.h>
#include <iostream>
#include "Components\TransformComponent.h"
#include "Components\PhysicsComponent.h"
#include "IAI.h"

struct AI_Homing: public IAi
{
	AI_Homing(entityx::Entity t):
	target(t)
	{
	}
	~AI_Homing()
	{

	}
	void Update(entityx::Entity self, entityx::EventManager &events, entityx::TimeDelta dt) override {

		auto position = self.component<TransformComponent>();
		auto physics = self.component<PhysicsComponent>();
		if (!target.valid())
			return;
		auto targetPosition = target.component<TransformComponent>();

		glm::vec2 toTarget = targetPosition->position - position->position;
		toTarget /= glm::length(toTarget);
		glm::vec2 velocity = toTarget * physics->maxSpeed;
		physics->currentSpeed = velocity;
	}

	entityx::Entity target;
};