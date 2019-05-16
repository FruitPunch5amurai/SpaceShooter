#pragma once
//EntityX
#include <EntityX/entityx.h>
#include <iostream>
#include "AIComponent.h"
struct AI_BlueGrunt : public IAi
{
	AI_BlueGrunt() {


	}
	~AI_BlueGrunt()
	{
		std::cout << "Blue Grunt Deleted" << std::endl;
	}
	void Update(entityx::Entity self) override {
		auto physics = self.component<PhysicsComponent>();

		physics->currentSpeed = glm::vec2(-physics->maxSpeed, 0);
		physics->direction = glm::vec2(-1, 0);
	}

};