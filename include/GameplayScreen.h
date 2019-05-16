#pragma once

#include <IGameScreen.h>
#include <chipmunk/chipmunk.h>
#include <vector>
#include <SpriteBatch.h>
#include <GLSLProgram.h>
#include <Camera.h>
#include <GLTexture.h>
#include <Window.h>
#include <GUI.h>
#include <DebugRenderer.h>
#include <ras_GUI.h>
#include <InputManager.h>
//SpaceShooter
#include "Player.h"
#include "CameraBackdrop.h"

//Lua
//extern "C" {
//#include <Lua/lua.h>
//#include <Lua/lauxlib.h>
//#include <Lua/lualib.h>
//}

#include "Systems/AnimationSystem.h"

class GameplayScreen : public Rasengine::IGameScreen
{
public:
	GameplayScreen(Rasengine::Window* window);
	~GameplayScreen();
	//Return the index of the next or previous screen when changing
	virtual int GetNextScreenIndex() const override;
	virtual int GetPreviousScreenIndex() const override;


	//Called at beggining and end of application
	virtual void Build() override;
	virtual void Destroy() override;

	//Called when a screen enters and exits focus
	virtual void OnEntry() override;
	virtual void OnExit() override;

	//Called in main game loop
	virtual void Update() override;
	virtual void Draw() override;

private:
	void CheckInput();
	Player m_player;

	Rasengine::Window* m_window;
	Rasengine::Camera2D m_camera;
	Rasengine::GLSLProgram m_textureProgram;

	CameraBackdrop m_cameraBackdrop;
};

