#pragma once
#include <InputManager.h>
//ChipMunk
#include <chipmunk/chipmunk.h>
//EntityX
#include <EntityX/entityx.h>

class Player
{
public:
	Player();
	~Player();

	entityx::Entity entityHandle;

	void Init(entityx::EntityManager* entityManager, cpSpace* space,Rasengine::InputManager* inputManager);
private:
};