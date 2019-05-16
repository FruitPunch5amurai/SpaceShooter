#pragma once

struct SpawnInfo {
	SpawnInfo() {}
	int x;
	int y;
	int name;
	std::string type;
};
struct Spawn {
	Spawn() {}
	float delay;
	int spawnNumber;
	std::vector<SpawnInfo> spawnInfo;
};
