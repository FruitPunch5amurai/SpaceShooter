#pragma once
//EntityX
#include <EntityX/entityx.h>
#include "AI\IAi.h"
struct AIComponent : public entityx::Component<AIComponent>
{
	AIComponent(AiId aiId) {

		this->aiId = aiId;
	}
	~AIComponent()
	{

	}
	AiId aiId;
private:
};