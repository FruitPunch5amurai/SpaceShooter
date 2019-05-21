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
#include "Components\TtLComponent.h"
#include "Components\MoveToTransformComponent.h"

#include "AI\IAI.h"

#include "CollisionBitMasks.h"

const char* PLAYER_ANIMATION_FILEPATH = "Animation/PlayerShip.json";
EnemyCreator::EnemyCreator(cpSpace* space, const glm::vec2& position, AiId enemyType)
	:m_enemyType(enemyType),
	m_position(position),
	m_space(space)
{
}
EnemyCreator::EnemyCreator(cpSpace* space, const std::vector<glm::vec2>& positions, AiId enemyType)
	: m_enemyType(enemyType),
	m_positions(positions),
	m_space(space)
{
}

void EnemyCreator::create(entityx::Entity entity)
{
	
	entity.assign<AIComponent>(m_enemyType);

	switch (m_enemyType)
	{
	case AI_ID_BLUE_GRUNT:
		entity.assign<TransformComponent>(m_position);
		entity.assign<SpriteComponent>("Animation/GruntShip.json", "Idle");
		entity.component<SpriteComponent>().get()->isStatic = true;
		entity.component<SpriteComponent>().get()->m_currentFrame = 3;
		entity.component<SpriteComponent>().get()->m_dir = glm::vec2(-1, 0);
		entity.assign<PhysicsComponent>(150.0f);
		entity.assign<AttackSpeedComponent>(50.0f);
		entity.assign<BoxColliderComponent>(m_space,
			m_position,
			entity.component<SpriteComponent>().get()->m_currentAnimation->at(0).dims,
			entity.component<SpriteComponent>().get()->m_spriteSheet->texture,
			Rasengine::ColorRGBA8(255.0f, 255.0f, 255.0f, 255.0f), entity,
			true, ENEMY_CATAGORY, ENEMY_CATAGORY_MASK);
		entity.assign<HealthComponent>(2);
		entity.assign<DamageComponent>(1);
		break;
	case AI_ID_PURPLE_GRUNT:
		entity.assign<TransformComponent>(m_position);
		entity.assign<SpriteComponent>("Animation/GruntShip.json", "Idle");
		entity.component<SpriteComponent>().get()->isStatic = true;
		entity.component<SpriteComponent>().get()->m_currentFrame = 0;
		entity.component<SpriteComponent>().get()->m_dir = glm::vec2(-1, 0);
		entity.assign<PhysicsComponent>(100.0f);
		entity.assign<AttackSpeedComponent>(50.0f);
		entity.assign<BoxColliderComponent>(m_space,
			m_position,
			entity.component<SpriteComponent>().get()->m_currentAnimation->at(0).dims,
			entity.component<SpriteComponent>().get()->m_spriteSheet->texture,
			Rasengine::ColorRGBA8(255.0f, 255.0f, 255.0f, 255.0f), entity,
			true, ENEMY_CATAGORY, ENEMY_CATAGORY_MASK);
		entity.assign<HealthComponent>(2);
		entity.assign<DamageComponent>(1);
		break;
	case AI_ID_GREEN_GRUNT:
		entity.assign<TransformComponent>(m_positions.at(0));
		entity.assign<SpriteComponent>("Animation/GruntShip.json", "Idle");
		entity.component<SpriteComponent>().get()->isStatic = true;
		entity.component<SpriteComponent>().get()->m_currentFrame =2;
		entity.component<SpriteComponent>().get()->m_dir = glm::vec2(-1, 0);
		entity.assign<PhysicsComponent>(160.0f);
		entity.assign<AttackSpeedComponent>(50.0f);
		entity.assign<BoxColliderComponent>(m_space,
			m_positions.at(0),
			entity.component<SpriteComponent>().get()->m_currentAnimation->at(0).dims,
			entity.component<SpriteComponent>().get()->m_spriteSheet->texture,
			Rasengine::ColorRGBA8(255.0f, 255.0f, 255.0f, 255.0f), entity,
			true, ENEMY_CATAGORY, ENEMY_CATAGORY_MASK);
		entity.assign<HealthComponent>(2);
		entity.assign<DamageComponent>(1);
		entity.assign<MoveToTransformComponent>(m_positions);
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

ProjectileCreator::ProjectileCreator(const Projectile &projectile, cpSpace * space)
	:m_space(space),
	m_projectile(projectile)
{
}

void ProjectileCreator::create(entityx::Entity entity)
{

	entity.assign<SpriteComponent>(m_projectile.resource, m_projectile.projectileType);
	entity.assign<PhysicsComponent>(m_projectile.speed);
	entity.component<PhysicsComponent>()->currentSpeed = glm::vec2(m_projectile.speed * m_projectile.direction.x,
		m_projectile.speed*m_projectile.direction.y);
	entity.component<PhysicsComponent>()->direction = m_projectile.direction;
	entity.assign<TtLComponent>(m_projectile.TtL);
	entity.assign<TransformComponent>(m_projectile.position);
	entity.assign<BoxColliderComponent>(
		m_space,
		m_projectile.position,
		entity.component<SpriteComponent>().get()->m_currentAnimation->at(0).dims,
		entity.component<SpriteComponent>().get()->m_spriteSheet->texture,
		Rasengine::ColorRGBA8(255.0f, 255.0f, 255.0f, 255.0f), entity,
		true,
		m_projectile.catagoryMask,
		m_projectile.bitMask);
	entity.assign<DamageComponent>(m_projectile.damage);
	entity.assign<HealthComponent>(1);
	if(m_projectile.aiType != 0)
		entity.assign<AIComponent>(m_projectile.aiType);
}

