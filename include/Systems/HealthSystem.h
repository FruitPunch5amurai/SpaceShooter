#pragma once
#include "Components\PhysicsComponent.h"
#include "Components\TransformComponent.h"
#include "Components\SpriteComponent.h"
#include "Components\AttackSpeedComponent.h"
#include "Components/BoxColliderComponent.h"
#include "Components\HealthComponent.h"
#include "Components\DamageComponent.h"
#include "Components\TtLComponent.h"
#include "Events/Event_Sound.h"
#include "AI\IAI.h"
//Rasengine
#include <LuaHelper.h>


//EntityX
#include <EntityX/System.h>

#include <string>
#include <GLM/glm.hpp>

#include "CollisionBitMasks.h"



using namespace entityx;

struct HealthSystem : public System<HealthSystem>
{

	HealthSystem()
	{

	}
	~HealthSystem()
	{

	}
	void update(EntityManager &entities, EventManager &events, TimeDelta dt) override
	{
		ComponentHandle<HealthComponent> health;
		ComponentHandle<BoxColliderComponent> boxColl;
		ComponentHandle<SpriteComponent> sprite;

		for (Entity ent : entities.entities_with_components(health, boxColl, sprite))
		{
			/*Check HP*/
			if (health.get()->currentHp <= 0)
			{
				if (ent.has_component<InputComponent>())
				{
					ent.remove<InputComponent>();
					events.emit<Event_Sound>("sounds/player_death.mp3");
				}
				if (ent.has_component<AIComponent>())
					ent.remove<AIComponent>();
				health.remove();
				boxColl.remove();
 				if (sprite.get()->m_spriteSheet->SetAnimation("Die") != nullptr)
				{
					sprite.get()->m_currentAnimation = sprite.get()->m_spriteSheet->SetAnimation("Die");
					sprite.get()->m_currentAnimationName = "Die";
					sprite.get()->m_currentFrame = 0;
					sprite.get()->m_lastAnimationStep = 0;
					sprite.get()->isStatic = false;
					ent.assign<TtLComponent>(480.0f);
					events.emit<Event_Sound>("sounds/enemy_explosion.mp3");
				}
				else
					ent.destroy();			
				continue;
			}
		}
	}
private:

};
