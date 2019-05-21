#pragma once
//SpaceShooter
#include "Events/Event_Sound.h"

//Rasengine
#include <AudioEngine.h>
//EntityX
#include <EntityX/System.h>

#include <iostream>
using namespace entityx;
struct SoundSystem : public System<SoundSystem>, public entityx::Receiver<SoundSystem>
{
	SoundSystem(Rasengine::AudioEngine* audioEngine)
	{
		m_audioEngine = audioEngine;
	}
	void configure(entityx::EventManager& events)
	{
		events.subscribe<Event_Sound>(*this);
	}
	void update(EntityManager &entities, EventManager &events, TimeDelta dt) override
	{

	}
	void receive(const Event_Sound& e)
	{
		m_audioEngine->PlaySoundFile(e.soundFile);
	}
private:
	Rasengine::AudioEngine* m_audioEngine;
};
