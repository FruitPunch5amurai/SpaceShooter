#pragma once

#include <string>

struct Event_Sound
{
	Event_Sound(std::string sound):
		soundFile(sound)
	{

	}
	std::string soundFile;
	int isLoop = 0;
};