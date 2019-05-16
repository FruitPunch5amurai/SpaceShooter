#pragma once
#include <GLM/glm.hpp>
//Rasengine
#include <InputManager.h>

struct PhysicsComponent : public entityx::Component<PhysicsComponent>
{
	PhysicsComponent(float speed) {
		this->maxSpeed = speed;
	}
	PhysicsComponent(float speed,glm::vec2& direction) {
		this->maxSpeed = speed;
		this->direction = direction;
	}

	glm::vec2 direction;
	glm::vec2 currentSpeed = glm::vec2(0,0);
	float maxSpeed;
};