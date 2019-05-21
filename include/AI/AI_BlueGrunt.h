#pragma once
//EntityX
#include <EntityX/entityx.h>
#include <iostream>
#include "Components\AIComponent.h"
struct AI_BlueGrunt : public IAi
{
	AI_BlueGrunt(entityx::Entity t) :
		player(t)
	{

	}
	~AI_BlueGrunt()
	{
		std::cout << "Blue Grunt Deleted" << std::endl;
	}
	void Update(entityx::Entity self, entityx::EventManager &events, entityx::TimeDelta dt) override {
		auto physics = self.component<PhysicsComponent>();
		auto position = self.component<TransformComponent>();
		auto atkSpeed = self.component<AttackSpeedComponent>();
		auto transform = self.component<TransformComponent>();
		auto sprite = self.component<SpriteComponent>();
		if (!player.valid())
			return;
		auto targetPosition = player.component<TransformComponent>();

		if (atkSpeed->timeAttack <= 0)
		{

			events.emit<Projectile>(transform->position,
				sprite->m_dir,
				100.0f,
				4000.0f,
				"Animation/Projectile.json",
				"EnemyShot1",
				2,	//Damage
				AI_ID_ENEMY_HOMING_PROJECTILE,
				ENEMY_BULLET_CATAGORY,
				ENEMY_BULLET_CATAGORY_MASK);

			atkSpeed->timeAttack = atkSpeed->atkSpeed;
		}

		/*Homing Logic*/
		glm::vec2 toTarget = targetPosition->position - position->position;
		toTarget /= glm::length(toTarget);
		glm::vec2 velocity = toTarget * physics->maxSpeed;
		physics->currentSpeed = velocity;

		/*Look At Logic*/
		sprite->m_dir = toTarget;


		/*physics->direction = glm::vec2(-1, 0);
		physics->currentSpeed = physics->maxSpeed * physics->direction;*/

		atkSpeed->timeAttack = atkSpeed->timeAttack - dt <= 0 ? 0 : atkSpeed->timeAttack - dt;
	}
	entityx::Entity player;

};