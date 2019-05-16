#pragma once
#include "Projectile.h"
#include "EntityCreator.h"
//Rasengine
#include <SpriteBatch.h>
#include <Camera.h>
//EntityX
#include <EntityX/System.h>

#include <iostream>
#include <queue>
#include <GLM/glm.hpp>
using namespace entityx;
/*TODO: Create Projectile QUEUE to process new projectile creations*/
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

	}
	void receive(const Projectile &projectile) {
		ProjectileCreator projectileCreator(projectile,m_space);
		projectileCreator.create(m_entities->create());
	}
private:
	cpSpace* m_space;
	EntityManager *m_entities;
};
