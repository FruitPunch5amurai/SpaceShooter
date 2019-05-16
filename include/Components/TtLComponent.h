#pragma once
#include <SDL/SDL.h>
/*
	Time to Live Component
*/
struct TtLComponent : public entityx::Component<TtLComponent> {
	TtLComponent(float time){
		maxTime = time + SDL_GetTicks();
		timeRemaining = maxTime;
	}
	float maxTime;
	float timeRemaining;
};