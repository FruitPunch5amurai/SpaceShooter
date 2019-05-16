#pragma once
//EntityX
#include <EntityX/entityx.h>
#include <iostream>
#include "AIComponent.h"
struct AI_BlueGrunt : public IAi
{
	AI_BlueGrunt() {


	}
	~AI_BlueGrunt()
	{
		std::cout << "Blue Grunt Deleted" << std::endl;
	}
	void Update(entityx::Entity self, entityx::EventManager &events, entityx::TimeDelta dt) override {
		auto physics = self.component<PhysicsComponent>();
		auto atkSpeed = self.component<AttackSpeedComponent>();
		auto transform = self.component<TransformComponent>();
		auto sprite = self.component<SpriteComponent>();
			
		if (atkSpeed->timeAttack <= 0)
		{
			events.emit<Projectile>(transform->position,
				glm::vec2(sprite->m_dir.x, sprite->m_dir.y),
				800.0f,
				1000.0f,
				"Animation/PlayerProjectile.json",
				"NormalShot",
				2,	//Damage
				ENEMY_BULLET_CATAGORY,
				ENEMY_BULLET_CATAGORY_MASK);
			atkSpeed->timeAttack = atkSpeed->atkSpeed;
		}

		physics->currentSpeed = glm::vec2(physics->maxSpeed, 0);
		physics->direction = glm::vec2(-1, 0);

		atkSpeed->timeAttack = atkSpeed->timeAttack - dt <= 0 ? 0 : atkSpeed->timeAttack - dt;
	}

};