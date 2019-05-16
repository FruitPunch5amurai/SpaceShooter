#pragma once
//SpaceShooter
#include "Components\PhysicsComponent.h"
#include "EntityCreator.h"
#include "AI\IAI.h"
#include "Wave.h"

//EntityX
#include <EntityX/System.h>

//Rasengine
#include <Camera.h>

#include <string>
#include <GLM/glm.hpp>
#include <time.h>       /* time */

using namespace entityx;
using namespace luabridge;
/*TODO: Create Enemy QUEUE to process Enemy Creation*/
struct LevelSystem : public System<LevelSystem>
{

	LevelSystem(Rasengine::Camera2D* camera)
	{
		m_camera = camera;
		/* initialize random seed: */
		/*srand(time(NULL));*/
		m_timeBeforeNextSpawn = m_timeUntilNextSpawn + SDL_GetTicks();
		m_running = 1;
	}
	void update(EntityManager &entities, EventManager &events, TimeDelta dt) override
	{
		if (m_randomMode)
		{
			if (SDL_GetTicks() > m_timeBeforeNextSpawn)
			{
				int x = m_camera->GetScreenDims().x/2;
				int y = m_camera->GetScreenDims().y/2;
				int randomNum = rand() % (y - (-y) + 1) + (-y);
				glm::vec2 position = glm::vec2(x, randomNum);

				EnemyCreator enemyCreation(s_entityXManager.systems.system<CollisionSystem>()->m_space,
					position,
					AI_ID_BLUE_GRUNT);
				enemyCreation.create(entities.create());
				m_timeBeforeNextSpawn = SDL_GetTicks() + m_spawnInterval;
			}
		}
		//if (m_running)
		//{
		//	if (m_timeBeforeNextSpawn < SDL_GetTicks())
		//	{
		//		for (SpawnInfo spawn : m_waves.at(m_currentWave).spawns.at(m_currentSpawn).spawnInfo)
		//		{
		//			s_entityXManager.systems.system<AiSystem>()->CreateEnemy(&entities, s_entityXManager.systems.system<CollisionSystem>()->m_space, glm::vec2(spawn.x, spawn.y), spawn.name);
		//		}
		//		m_timeBeforeNextSpawn = SDL_GetTicks() + m_waves.at(m_currentWave).spawns.at(m_currentSpawn).delay;
		//		m_currentSpawn++;
		//		if (m_currentSpawn >= m_waves.at(m_currentWave).spawns.size())
		//		{
		//			m_currentSpawn = 0;
		//			m_currentWave++;
		//		}
		//		if (m_currentWave >= m_waves.size())
		//		{
		//			m_currentWave = 0;
		//			m_currentSpawn = 0;
		//			m_running = 0;				
		//		}
		//	}
		//}
	}
	void LoadLevel(std::string levelName)
	{
		Rasengine::LuaHelper luaHelper;
		lua_State* L = luaHelper.LoadScript(levelName);
		LuaRef wavesRef = getGlobal(L, "Waves");
		for (int i = 0; i < wavesRef.length();i++)
		{
			LuaRef waveRef = wavesRef[i + 1]["Wave"];
			for (int j = 0; j < waveRef.length();j++)
			{
				m_waves.emplace_back();
				m_waves.back().waveNumber = i + 1;
				LuaRef spawnRef = waveRef[j + 1]["Spawns"];
				for (int k = 0; k < spawnRef.length();k++)
				{					
					m_waves.back().spawns.emplace_back();
					m_waves.back().spawns.back().spawnNumber = j;
					m_waves.back().spawns.back().delay = spawnRef[k + 1]["Delay"].cast<float>();
					LuaRef enemiesRef = spawnRef[k + 1]["Enemies"];
					for (int l = 0; l < enemiesRef.length();l++)
					{
						m_waves.back().spawns.back().spawnInfo.emplace_back();
						m_waves.back().spawns.back().spawnInfo.back().name = enemiesRef[l+1]["name"].cast<int>();
						m_waves.back().spawns.back().spawnInfo.back().type = "Enemy";
						m_waves.back().spawns.back().spawnInfo.back().x = enemiesRef[l+1]["x"].cast<float>();
						m_waves.back().spawns.back().spawnInfo.back().y = enemiesRef[l+1]["y"].cast<float>();
					}
				}
			}
		}
		m_timeBeforeNextSpawn = m_timeUntilNextSpawn + SDL_GetTicks();
	}
private:
	std::string m_currentLevel;
	int m_currentWave = 0;
	int m_currentSpawn = 0;
	int m_running = 0;
	std::vector<Wave> m_waves;
	Rasengine::Camera2D* m_camera;

	float m_timeUntilNextSpawn = 500;

	int m_startLevel = 0;
	//Random Spawn Mode
	int m_randomMode = 1;
	int m_timeBeforeNextSpawn = 0;
	int m_spawnInterval = 1000;

};
