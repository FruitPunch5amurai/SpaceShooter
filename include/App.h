#pragma once

#include <IMainGame.h>
#include "GameplayScreen.h"
class App : public Rasengine::IMainGame
{
public:
	App();
	~App();

	virtual void OnInit() override;
	virtual void AddScreens() override;
	virtual void OnExit() override;

private:
	std::unique_ptr<GameplayScreen> m_gamePlayScreen = nullptr;
};

