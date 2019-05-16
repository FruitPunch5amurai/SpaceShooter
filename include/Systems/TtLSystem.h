#pragma once
#include "EntityXManager.h"
#include "Components\TtLComponent.h"
//Rasengine
#include <Camera.h>
//EntityX
#include <EntityX/System.h>

#include <iostream>
#include <GLM/glm.hpp>
using namespace entityx;
struct TtLSystem : public System<TtLSystem>
{
	TtLSystem()
	{

	}
	void update(EntityManager &entities, EventManager &events, TimeDelta dt) override
	{
		ComponentHandle<TtLComponent> ttl;
		for (Entity ent : entities.entities_with_components(ttl))
		{
			if (ttl->timeRemaining < SDL_GetTicks())
			{
				ent.destroy();
			}
		}
	}
private:
};
