#pragma once
#include <GLM/glm.hpp>

struct TransformComponent
{
	TransformComponent() {
		position.x = 0.0f;
		position.y = 0.0f;
	}
	TransformComponent(const glm::vec2& pos) {
		position = pos;
	}
	glm::vec2 position;
	glm::vec2 scale;
	float rotation;
};
struct MouseComponent 
{
	MouseComponent()
	{
		position.x = 0.0f;
		position.y = 0.0f;
	}
	MouseComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}
	glm::vec2 position;
};