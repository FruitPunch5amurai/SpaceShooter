#pragma once

#include "ICreatable.h"
#include "AI/IAI.h"
#include "Projectile.h"

#include <GLM/glm.hpp>
#include <InputManager.h>



class EnemyCreator : public ICreatable
{
public:
	EnemyCreator(cpSpace* space, const glm::vec2& position, AiId enemyType);
	EnemyCreator(cpSpace* space, const std::vector<glm::vec2>& positions, AiId enemyType);

	void create(entityx::Entity entity);
private:
	AiId m_enemyType;
	glm::vec2 m_position;
	std::vector<glm::vec2> m_positions;
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
class ProjectileCreator : public ICreatable
{
public:
	ProjectileCreator(const Projectile &projectile, cpSpace * space);

	void create(entityx::Entity entity);
private:
	Projectile m_projectile;
	cpSpace* m_space;
};