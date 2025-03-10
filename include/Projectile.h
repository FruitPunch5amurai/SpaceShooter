#pragma once

#include "AI\IAi.h"

#include <string>
#include <chipmunk/chipmunk.h>
#include <GLM/glm.hpp>

struct Projectile
{
	Projectile(const glm::vec2& pos,
		const glm::vec2& dir,
		float spd,
		float T,
		const char* res, 
		const char* type,
		int d,
		AiId ai,
		cpBitmask catMask = 0x0,
		cpBitmask colMask = 0x0) : position(pos),
		direction(dir), 
		aiType(ai),
		speed(spd), 
		TtL(T), 
		resource(res),
		projectileType(type),
		damage(d),
		catagoryMask(catMask),
		bitMask(colMask){};
	

	glm::vec2 position;
	glm::vec2 direction;
	int damage;
	float speed;
	float TtL;
	const char*  resource;
	const char*  projectileType;
	cpBitmask catagoryMask;
	cpBitmask bitMask;
	AiId aiType;
};