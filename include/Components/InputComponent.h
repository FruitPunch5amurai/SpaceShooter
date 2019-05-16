#pragma once
#include <GLM/glm.hpp>
//Rasengine
#include <InputManager.h>

struct InputComponent : public entityx::Component<InputComponent>
{
	InputComponent(Rasengine::InputManager *inputManager) {
		this->inputManager = inputManager;
	}

	Rasengine::InputManager* inputManager;
};