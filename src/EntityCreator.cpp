#include "EntityCreator.h"

#include "Components\PhysicsComponent.h"
#include "Components\TransformComponent.h"
#include "Components\SpriteComponent.h"
#include "Components\AttackSpeedComponent.h"
#include "Components/BoxColliderComponent.h"
#include "Components\HealthComponent.h"
#include "Components\DamageComponent.h"
#include "Components\AIComponent.h"

#include "CollisionBitMasks.h"
EnemyCreator::EnemyCreator(cpSpace* space, const glm::vec2& position, AiId enemyType)
	:m_enemyType(enemyType),
	m_position(position),
	m_space(space)
{
}

void EnemyCreator::create(entityx::Entity entity)
{
	entity.assign<TransformComponent>(m_position);
	entity.assign<AIComponent>(m_enemyType);

	switch (m_enemyType)
	{
	case AI_ID_BLUE_GRUNT:
		entity.assign<SpriteComponent>("Animation/GruntShip.json", "Idle");
		entity.component<SpriteComponent>().get()->isStatic = true;
		entity.component<SpriteComponent>().get()->m_currentFrame = 3;
		entity.component<SpriteComponent>().get()->m_dir = glm::vec2(-1, 0);
		entity.assign<PhysicsComponent>(300.0f);
		entity.assign<AttackSpeedComponent>(1.0f);
		entity.assign<BoxColliderComponent>(m_space,
			m_position,
			entity.component<SpriteComponent>().get()->m_currentAnimation->at(0).dims,
			entity.component<SpriteComponent>().get()->m_spriteSheet->texture,
			Rasengine::ColorRGBA8(255.0f, 255.0f, 255.0f, 255.0f), entity,
			true, ENEMY_CATAGORY, ENEMY_CATAGORY_MASK);
		entity.assign<HealthComponent>(2);
		entity.assign<DamageComponent>(1);
		break;
	default:
		entity.destroy();
		break;
	}
}
