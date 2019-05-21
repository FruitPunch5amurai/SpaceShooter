#pragma once
//EntityX
#include <EntityX/entityx.h>
#include <vector>
#include <GLM/glm.hpp>
struct MoveToTransformComponent : public entityx::Component<MoveToTransformComponent>
{
	MoveToTransformComponent(const std::vector<glm::vec2>& moveTo) {
		toPositions = moveTo;
	}
	std::vector<glm::vec2> toPositions;
};