#pragma once
#include "Events/Event_Sound.h"

#include "Components\SpriteComponent.h"
//#include "Components\TransformComponent.h"
#include "Components\InputComponent.h"
#include "Components\PhysicsComponent.h"
#include "Components/BoxColliderComponent.h"
#include "Components\AttackSpeedComponent.h"
#include "Projectile.h"
#include "CollisionBitMasks.h"
//Rasengine
#include <SpriteBatch.h>
#include <Camera.h>
//EntityX
#include <EntityX/System.h>

#include <iostream>
#include <GLM/glm.hpp>

/*
	Player Controller
*/
using namespace entityx;

struct PlayerFire
{
	PlayerFire() {};
};

struct PlayerControllerSystem : public System<PlayerControllerSystem>
{
	PlayerControllerSystem(Rasengine::Camera2D* camera)
	{
		this->camera = camera;
	}
	void update(EntityManager &entities, EventManager &events, TimeDelta dt) override
	{
		ComponentHandle<SpriteComponent> sprite;
		ComponentHandle<PhysicsComponent> physics;
		ComponentHandle<InputComponent> input;
		ComponentHandle<BoxColliderComponent> box;
		ComponentHandle<AttackSpeedComponent> atkSpeed;

		//TODO: Move some of this logic to a different system
		for (Entity ent : entities.entities_with_components(input, sprite, physics, box, atkSpeed))
		{
			physics->direction.x = physics->direction.y = 0;

			glm::vec2 centerPosition;
			centerPosition.x = cpBodyGetPosition(box->m_body).x;
			centerPosition.y = cpBodyGetPosition(box->m_body).y;

			physics->currentSpeed = glm::vec2(physics->maxSpeed, physics->maxSpeed);
			physics->direction = glm::vec2(0.0f, 0.0f);

			if (input->inputManager->isKeyDown(SDLK_w))
			{
				if (!camera->IsBoxInView(glm::vec2(centerPosition.x,centerPosition.y+3), sprite->m_currentAnimation->at(sprite->m_currentFrame).dims))
					physics->direction = glm::vec2(physics->direction.x, 0.0f);
				else
					physics->direction = glm::vec2(physics->direction.x, 1.0f);
			}
			if (input->inputManager->isKeyDown(SDLK_s))
			{
				if (!camera->IsBoxInView(glm::vec2(centerPosition.x, centerPosition.y - sprite->m_currentAnimation->at(sprite->m_currentFrame).dims.y), sprite->m_currentAnimation->at(sprite->m_currentFrame).dims))
					physics->direction = glm::vec2(physics->direction.x, 0.0f);
				else
					physics->direction = glm::vec2(physics->direction.x, -1.0f);
			}
			if (input->inputManager->isKeyDown(SDLK_a))
			{
				if (!camera->IsBoxInView(glm::vec2(centerPosition.x - sprite->m_currentAnimation->at(sprite->m_currentFrame).dims.x, centerPosition.y), sprite->m_currentAnimation->at(sprite->m_currentFrame).dims))
					physics->direction = glm::vec2(0.0f, physics->direction.y);
				else
					physics->direction = glm::vec2(-1.0f, physics->direction.y);
			}
			if (input->inputManager->isKeyDown(SDLK_d))
			{				
				if (!camera->IsBoxInView(glm::vec2(centerPosition.x + sprite->m_currentAnimation->at(sprite->m_currentFrame).dims.x/2, centerPosition.y), sprite->m_currentAnimation->at(sprite->m_currentFrame).dims))
					physics->direction = glm::vec2(0.0f, physics->direction.y);
				else
					physics->direction = glm::vec2(1.0f, physics->direction.y);
			}
			physics->currentSpeed = glm::vec2(physics->currentSpeed.x * physics->direction.x, 
				physics->currentSpeed.y * physics->direction.y);
			if (input->inputManager->isKeyDown(SDLK_SPACE))
			{
				if (atkSpeed->timeAttack <= 0)
				{
					events.emit<Event_Sound>("sounds/laser.wav");
					events.emit<Projectile>(centerPosition, 
						sprite->m_dir,
						800.0f, 
						400.0f, 
						"Animation/Projectile.json",
						"NormalShot",
						2,	//Damage
						AI_ID_NONE,
						PLAYER_BULLET_CATAGORY,
						PLAYER_BULLET_CATAGORY_MASK);
					atkSpeed->timeAttack = atkSpeed->atkSpeed;
				}
			}
			atkSpeed->timeAttack = atkSpeed->timeAttack - dt <= 0 ? 0 : atkSpeed->timeAttack -  dt;
		}
	}
private:
	Rasengine::Camera2D* camera;
};
