#pragma once
//EntityX
#include <EntityX/entityx.h>
#include <iostream>
#include "Components\AIComponent.h"
#include "Components\PhysicsComponent.h"
#include "Components\AttackSpeedComponent.h"
#include "Components\TransformComponent.h"
#include "Components\SpriteComponent.h"
#include "Components\MoveToTransformComponent.h"
#include <vector>
#include <GLM/glm.hpp>
struct AI_GreenGrunt : public IAi
{
	AI_GreenGrunt(entityx::Entity t) :
		player(t)
	{

	}
	~AI_GreenGrunt()
	{
		std::cout << "Green Grunt Deleted" << std::endl;
	}
	void Update(entityx::Entity self, entityx::EventManager &events, entityx::TimeDelta dt) override {
		auto physics = self.component<PhysicsComponent>();
		auto atkSpeed = self.component<AttackSpeedComponent>();
		auto transform = self.component<TransformComponent>();
		auto sprite = self.component<SpriteComponent>();
		auto moveToTransform = self.component<MoveToTransformComponent>();


		if (atkSpeed->timeAttack <= 0)
		{

		}
		if (indexIntoPositions >= moveToTransform->toPositions.size())
		{
			physics->direction = glm::vec2(-1, 0);
			physics->currentSpeed = physics->maxSpeed * physics->direction;
			return;
		}

		glm::vec2 targetPosition = moveToTransform->toPositions.at(indexIntoPositions);

		/*Homing Logic*/
		glm::vec2 toTarget = targetPosition - transform->position;
		float length = glm::length(toTarget);
		toTarget /= length;
		glm::vec2 velocity = toTarget * physics->maxSpeed;
		physics->currentSpeed = velocity;

		float distance = glm::distance(targetPosition, transform->position);
		if (distance <= 5.0f)
		{
			indexIntoPositions++;
		}
	}
	entityx::Entity player;
	int indexIntoPositions = 1;

};