#include "EntityCreator.h"

#include "Components\PhysicsComponent.h"
#include "Components\TransformComponent.h"
#include "Components\SpriteComponent.h"
#include "Components\AttackSpeedComponent.h"
#include "Components/BoxColliderComponent.h"
#include "Components\HealthComponent.h"
#include "Components\DamageComponent.h"
#include "Components\AIComponent.h"
#include "Components\InputComponent.h"

#include "CollisionBitMasks.h"

const char* PLAYER_ANIMATION_FILEPATH = "Animation/PlayerShip.json";
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
		entity.assign<AttackSpeedComponent>(10.0f);
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

PlayerCreator::PlayerCreator(cpSpace * space, Rasengine::InputManager * inputManager)
	:m_space(space),
	m_inputManager(inputManager)
{

}

void PlayerCreator::create(entityx::Entity entity)
{
	entity.assign<SpriteComponent>(PLAYER_ANIMATION_FILEPATH, "Idle");
	entity.assign<PhysicsComponent>(150.0f);
	entity.assign<InputComponent>(m_inputManager);
	entity.assign<TransformComponent>(glm::vec2(-50.0f, 0.0f));
	entity.assign<AttackSpeedComponent>(10.0f);
	entity.assign<BoxColliderComponent>(
		m_space,
		glm::vec2(-50.0f, 0.0f),
		entity.component<SpriteComponent>().get()->m_currentAnimation->at(0).dims,
		entity.component<SpriteComponent>().get()->m_spriteSheet->texture,
		Rasengine::ColorRGBA8(255.0f, 255.0f, 255.0f, 255.0f), entity,
		true, PLAYER_CATAGORY, PLAYER_CATAGORY_MASK);
	entity.assign<HealthComponent>(1);
	entity.assign<DamageComponent>(1);
}
