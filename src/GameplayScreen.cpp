#include "GameplayScreen.h"
#include <iostream>
#include <SDL/SDL.h>
#include <random>
#include <algorithm>

//SpaceShooter
#include "Systems\PlayerControllerSystem.h"
#include "Systems\MotionSystem.h"
#include "Systems\TtLSystem.h"
#include "Systems\AiSystem.h"
#include "Systems\CollisionSystem.h"
#include "Systems\ProjectileSystem.h"
#include "Systems\LevelSystem.h"
#include "Systems\HealthSystem.h"
#include "EntityXManager.h"

//Rasengine
#include <LuaHelper.h>
#include <ResourceManager.h>
#include <IMainGame.h>
#include <LuaBridge/LuaBridge.h>

//Lua
//#include <LuaW/luawrapper.hpp>
//#include <LuaW/luawrapperutil.hpp>

Uint32 previousTicks = SDL_GetTicks();
const float DESIRED_FPS = 60.0f; // FPS the game is designed to run at
const int MAX_PHYSICS_STEPS = 6; // Max number of physics steps per frame
const float MS_PER_SECOND = 1000; // Number of milliseconds in a second
const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS; // The desired frame time per frame
const float MAX_DELTA_TIME = 1.0f; // Maximum size of deltaTime

GameplayScreen::GameplayScreen(Rasengine::Window* window) :m_window(window)
{
}


GameplayScreen::~GameplayScreen()
{

}

int GameplayScreen::GetNextScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

int GameplayScreen::GetPreviousScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

void GameplayScreen::Build()
{

}

void GameplayScreen::Destroy()
{
	s_entityXManager.entities.reset();
}

void GameplayScreen::OnEntry()
{
	// Compile our color shaders
	m_textureProgram.CompileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	m_textureProgram.AddAttribute("vertexPosition");
	m_textureProgram.AddAttribute("vertexColor");
	m_textureProgram.AddAttribute("vertexUV");
	m_textureProgram.LinkShaders();

	//Init Camera
	m_camera.Init(m_window->getScreenWidth(), m_window->getScreenHeight());

	//Add Systems
	s_entityXManager.systems.add<MotionSystem>();
	s_entityXManager.systems.add<CollisionSystem>();
	s_entityXManager.systems.add<ProjectileSystem>(s_entityXManager.systems.system<CollisionSystem>()->m_space, s_entityXManager.entities);
	s_entityXManager.systems.add<PlayerControllerSystem>(&m_camera);
	s_entityXManager.systems.add<AnimationSystem>(&m_camera);
	s_entityXManager.systems.add<TtLSystem>();
	s_entityXManager.systems.add<AiSystem>(&m_camera, player);
	s_entityXManager.systems.add<LevelSystem>(&m_camera);
	s_entityXManager.systems.add<HealthSystem>();
	s_entityXManager.systems.configure();

	m_cameraBackdrop.Init("Textures/starfield.png", m_window, m_camera);

	//Create Player
	PlayerCreator playerCreator(s_entityXManager.systems.system<CollisionSystem>()->m_space, &m_game->inputManager);
	player = s_entityXManager.entities.create();
	playerCreator.create(player);

	//s_entityXManager.systems.system<AiSystem>()->CreateEnemy(&s_entityXManager.entities, s_entityXManager.systems.system<CollisionSystem>()->m_space, glm::vec2(0.0f, 0.0f),"BLUE_GRUNT");
	s_entityXManager.systems.system<LevelSystem>()->LoadLevel("lua_scripts/levels/level.lua");
}


void GameplayScreen::Update()
{
	CheckInput();

	// Calculate the frameTime in milliseconds
	Uint32 newTicks = SDL_GetTicks();
	Uint32 frameTime = newTicks - previousTicks;
	previousTicks = newTicks; // Store newTicks in previousTicks so we can use it next frame
							  // Get the total delta time

	float totalDeltaTime = (float)frameTime / DESIRED_FRAMETIME;

	int i = 0; // This counter makes sure we don't spiral to death!
			   // Loop while we still have steps to process.

	while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS) {
		// The deltaTime should be the the smaller of the totalDeltaTime and MAX_DELTA_TIME
		float deltaTime = min(totalDeltaTime, MAX_DELTA_TIME);
		//Update Systems
		s_entityXManager.systems.update_all(deltaTime);

		// Since we just took a step that is length deltaTime, subtract from totalDeltaTime
		totalDeltaTime -= deltaTime;
		// Increment our frame counter so we can limit steps to MAX_PHYSICS_STEPS
		i++;
	}

	//Update Camera
	m_camera.Update();
	//Update Physics Simulation
	cpSpaceStep(s_entityXManager.systems.system<CollisionSystem>()->m_space, 1.0f / 60.0f);
}

void GameplayScreen::Draw()
{
	// Set the base depth to 1.0
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	m_textureProgram.Use();

	//Upload Texture Uniform
	GLint texutreUniform = m_textureProgram.GetUnifromLocation("mySampler");
	glUniform1i(texutreUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	glm::mat4 projectionMatrix = m_camera.GetCameraMatrix();
	GLint pUniform = m_textureProgram.GetUnifromLocation("transformationMatrix");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_cameraBackdrop.Draw();

	s_entityXManager.systems.system<AnimationSystem>()->render(s_entityXManager.entities);
	//s_entityXManager.systems.system<CollisionSystem>()->render(s_entityXManager.entities,&m_camera);


	m_textureProgram.Unuse();
}

void GameplayScreen::CheckInput()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt))
	{
		m_game->OnSDLEvent(evnt);
	}
}


void GameplayScreen::OnExit()
{

}
