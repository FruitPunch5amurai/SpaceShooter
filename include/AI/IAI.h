#pragma once
//EntityX
#include <EntityX/entityx.h>

typedef uint32_t AiId;

static const AiId AI_ID_NONE = 0;
static const AiId AI_ID_PURPLE_GRUNT = 1;
static const AiId AI_ID_RED_GRUNT = 2;
static const AiId AI_ID_GREEN_GRUNT = 3;
static const AiId AI_ID_BLUE_GRUNT = 4;

class IAi
{
public:
	IAi() {


	}
	~IAi()
	{

	}
	virtual void Update(entityx::Entity self) {}	
};
typedef std::shared_ptr<IAi> IAiSP;