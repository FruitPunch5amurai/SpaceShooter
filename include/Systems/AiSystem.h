#pragma once


#include "AI/IAi.h"

#include "Components\AI_BlueGrunt.h"
#include "AI\AI_HomingProjectile.h"
#include "Components\AIComponent.h"

//Rasengine
#include <LuaHelper.h>


//EntityX
#include <EntityX/System.h>

#include <string>
#include <GLM/glm.hpp>




using namespace entityx;

struct AiSystem : public System<AiSystem>, public entityx::Receiver<AiSystem>
{
	AiSystem(Rasengine::Camera2D* camera,entityx::Entity player)
	{
		this->m_player = player;
		this->m_camera = camera;
	}
	~AiSystem()
	{
		
	}
	void configure(entityx::EventManager& events)
	{
		events.subscribe<ComponentAddedEvent<AIComponent>>(*this);
		events.subscribe<ComponentRemovedEvent<AIComponent>>(*this);
	}
	void receive(const entityx::ComponentAddedEvent<AIComponent>& e)
	{
		IAiSP spAi;

		switch (e.component->aiId)
		{
		case AI_ID_BLUE_GRUNT:
			spAi.reset(new AI_BlueGrunt());
			break;
		case AI_ID_ENEMY_HOMING_PROJECTILE:
			spAi.reset(new AI_HomingProjectile(m_player));
			break;
		default:
			break;
		}
		m_aiMap[e.entity.id()] = spAi;
	}
	void receive(const ComponentRemovedEvent<AIComponent> &e)
	{
		m_aiMap.erase(e.entity.id());
	}
	void update(EntityManager &entities, EventManager &events, TimeDelta dt) override
	{
		ComponentHandle<AIComponent> ai;
		ComponentHandle<TransformComponent> pos;

		for (Entity ent : entities.entities_with_components(ai,pos))
		{			
			/*Check out of bounds*/
			if (pos->position.x < -m_camera->GetScreenDims().x / 2)
			{
				std::cout << "Entity out of bounds" << std::endl;
				ent.destroy();
				continue;
			}
			AiMap::iterator it = m_aiMap.find(ent.id());
			if (it != end(m_aiMap))
			{
				it->second->Update(ent,events,dt);
			}
		}
	}
private:
	typedef std::map<entityx::Entity::Id, IAiSP> AiMap;
	entityx::Entity m_player;
	AiMap m_aiMap;
	Rasengine::Camera2D* m_camera;
};
