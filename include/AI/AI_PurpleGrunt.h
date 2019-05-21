#pragma once
//EntityX
#include <EntityX/entityx.h>
#include <iostream>
#include "Components\AIComponent.h"
struct AI_PurpleGrunt : public IAi
{
	AI_PurpleGrunt(entityx::Entity t) :
		player(t)
	{

	}
	~AI_PurpleGrunt()
	{
		std::cout << "Purple Grunt Deleted" << std::endl;
	}
	void Update(entityx::Entity self, entityx::EventManager &events, entityx::TimeDelta dt) override {
		auto physics = self.component<PhysicsComponent>();
		auto atkSpeed = self.component<AttackSpeedComponent>();
		auto transform = self.component<TransformComponent>();
		auto sprite = self.component<SpriteComponent>();
			
		if (atkSpeed->timeAttack <= 0)
		{
			if (!player.valid())
				return;
			glm::vec2 toTarget = transform->position - player.component<TransformComponent>()->position;
			toTarget /= glm::length(toTarget);

			//Spawn regular projectile
			events.emit<Projectile>(transform->position,
				-toTarget,
				250.0f,
				10000.0f,
				"Animation/Projectile.json",
				"EnemyShot1",
				2,	//Damage
				AI_ID_NONE,
				ENEMY_BULLET_CATAGORY,
				ENEMY_BULLET_CATAGORY_MASK);

			atkSpeed->timeAttack = atkSpeed->atkSpeed;
		}

		physics->direction = glm::vec2(-1, 0);
		physics->currentSpeed = physics->maxSpeed * physics->direction;

		atkSpeed->timeAttack = atkSpeed->timeAttack - dt <= 0 ? 0 : atkSpeed->timeAttack - dt;
	}
	entityx::Entity player;

};