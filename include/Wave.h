#pragma once

#include "Spawn.h"
struct Wave {
	Wave() {}

	std::vector<Spawn> spawns;
	int waveNumber;
};