#pragma once
#include "Components\SpriteComponent.h"
#include "Components/BoxColliderComponent.h"
#include "Components\InputComponent.h"
#include "Components\PhysicsComponent.h"
#include "Components\TtLComponent.h"
#include "Components\DamageComponent.h"
#include "Components\HealthComponent.h"
#include "Projectile.h"
//Rasengine
#include <SpriteBatch.h>
#include <Camera.h>
//EntityX
#include <EntityX/System.h>

#include <iostream>
#include <queue>
#include <GLM/glm.hpp>
using namespace entityx;
struct ProjectileSystem : public System<ProjectileSystem>, public Receiver<ProjectileSystem>
{
	ProjectileSystem(cpSpace* space, EntityManager &entities)
	{
		m_space = space;
		m_entities = &entities;
	}

	void configure(entityx::EventManager &event_manager) {
		event_manager.subscribe<Projectile>(*this);
	}
	void update(EntityManager &entities, EventManager &events, TimeDelta dt) override
	{
		//ComponentHandle<HealthComponent> health;
		//ComponentHandle<TtLComponent> ttl;
		//ComponentHandle<DamageComponent> damage;
		//ComponentHandle<BoxColliderComponent> boxColl;

		//for (Entity ent : entities.entities_with_components(health, ttl, damage, boxColl))
		//{
		//	/*Check HP*/
		//	if (health.get()->currentHp <= 0)
		//	{
		//		ShapeFreeWrap(boxColl->m_space,boxColl->m_shape,NULL);
		//		BodyFreeWrap(boxColl->m_space, boxColl->m_body, NULL);

		//		boxColl->m_shape = nullptr;
		//		boxColl->m_body = nullptr;

		//		boxColl->m_entityHandle.destroy();
		//	}
		//}
	}
	void receive(const Projectile &projectile) {
		entityx::Entity entityHandle = m_entities->create();

		entityHandle.assign<SpriteComponent>(projectile.resource, projectile.projectileType);
		entityHandle.assign<PhysicsComponent>(projectile.speed);
		entityHandle.component<PhysicsComponent>()->currentSpeed = glm::vec2(projectile.speed*projectile.direction.x, projectile.speed*projectile.direction.y);
		entityHandle.component<PhysicsComponent>()->direction = projectile.direction;
		entityHandle.assign<TtLComponent>(projectile.TtL);
		entityHandle.assign<TransformComponent>(projectile.position);
		entityHandle.assign<BoxColliderComponent>(
			m_space,
			projectile.position,
			entityHandle.component<SpriteComponent>().get()->m_currentAnimation->at(0).dims,
			entityHandle.component<SpriteComponent>().get()->m_spriteSheet->texture,
			Rasengine::ColorRGBA8(255.0f, 255.0f, 255.0f, 255.0f), entityHandle,
			true,
			projectile.catagoryMask,
			projectile.bitMask);
		entityHandle.assign<DamageComponent>(projectile.damage);
		entityHandle.assign<HealthComponent>(1);
	}
private:
	cpSpace* m_space;
	EntityManager *m_entities;
};
