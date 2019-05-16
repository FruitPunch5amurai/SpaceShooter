#pragma once
#include "Components\SpriteComponent.h"
//#include "Components\TransformComponent.h"
#include "Components/BoxColliderComponent.h"
#include "Components\InputComponent.h"
#include "Components\PhysicsComponent.h"
//Rasengine
#include <SpriteBatch.h>
#include <Camera.h>
//EntityX
#include <EntityX/System.h>

#include <iostream>
#include <GLM/glm.hpp>
using namespace entityx;
struct MotionSystem : public System<MotionSystem>
{
	MotionSystem()
	{

	}
	void update(EntityManager &entities, EventManager &events, TimeDelta dt) override
	{
		ComponentHandle<SpriteComponent> sprite;
		ComponentHandle<BoxColliderComponent> box;
		ComponentHandle<TransformComponent> pos;
		ComponentHandle<PhysicsComponent> physics;
		for (Entity ent : entities.entities_with_components(box,pos, sprite, physics))
		{
			cpBodySetVelocity(box->m_body, cpv(physics->currentSpeed.x * physics->direction.x,
					physics->currentSpeed.y * physics->direction.y));
			pos->position = glm::vec2(cpBodyGetPosition(box->m_body).x, cpBodyGetPosition(box->m_body).y);
		}
	}
private:

};
