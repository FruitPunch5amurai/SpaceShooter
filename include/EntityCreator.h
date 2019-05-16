#pragma once

#include "ICreatable.h"
#include "AI/IAI.h"

#include <GLM/glm.hpp>
#include <chipmunk/chipmunk.h>
#include <InputManager.h>



class EnemyCreator : public ICreatable
{
public:
	EnemyCreator(cpSpace* space, const glm::vec2& position, AiId enemyType);

	void create(entityx::Entity entity);
private:
	AiId m_enemyType;
	glm::vec2 m_position;
	cpSpace* m_space;
};
class PlayerCreator : public ICreatable
{
public:
	PlayerCreator(cpSpace* space, Rasengine::InputManager* inputManager);

	void create(entityx::Entity entity);
private:
	cpSpace* m_space;
	Rasengine::InputManager* m_inputManager;
};