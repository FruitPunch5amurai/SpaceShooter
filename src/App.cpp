#include <ScreenList.h>
#include "App.h"


App::App()
{
	m_screenWidth = 800;
	m_screenHeight = 600;
	m_windowTitle = "SpaceShooter";
}


App::~App()
{
}

void App::OnInit()
{
}

void App::AddScreens()
{
	m_gamePlayScreen = std::make_unique<GameplayScreen>(&m_window);

	m_screenList->AddScreen(m_gamePlayScreen.get());
	m_screenList->SetScreen(m_gamePlayScreen->GetIndex());

}

void App::OnExit()
{
}
