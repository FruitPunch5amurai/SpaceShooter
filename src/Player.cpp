//SpaceShooter
#include "Player.h"
#include "Components\InputComponent.h"
#include "Components\PhysicsComponent.h"
#include "Components\TransformComponent.h"
#include "Components\SpriteComponent.h"
#include "Components\AttackSpeedComponent.h"
#include "Components\BoxColliderComponent.h"
#include "Components\HealthComponent.h"
#include "Components\DamageComponent.h"
#include "CollisionBitMasks.h"

const char* PLAYER_ANIMATION_FILEPATH = "Animation/PlayerShip.json";

Player::Player()
{

}
Player::~Player()
{

}

void Player::Init(entityx::EntityManager* entityManager, cpSpace* space,Rasengine::InputManager* inputManager)
{
	entityHandle = entityManager->create();
	entityHandle.assign<SpriteComponent>(PLAYER_ANIMATION_FILEPATH, "Idle");
	entityHandle.assign<PhysicsComponent>(150.0f);
	entityHandle.assign<InputComponent>(inputManager);
	entityHandle.assign<TransformComponent>(glm::vec2(-50.0f, 0.0f));
	entityHandle.assign<AttackSpeedComponent>(10.0f);
	entityHandle.assign<BoxColliderComponent>(
		space,
		glm::vec2(-50.0f,0.0f),
		entityHandle.component<SpriteComponent>().get()->m_currentAnimation->at(0).dims,
		entityHandle.component<SpriteComponent>().get()->m_spriteSheet->texture,
		Rasengine::ColorRGBA8(255.0f, 255.0f, 255.0f, 255.0f), entityHandle,
		true, PLAYER_CATAGORY,PLAYER_CATAGORY_MASK);
	entityHandle.assign<HealthComponent>(1);
	entityHandle.assign<DamageComponent>(1);
}  	
