#pragma once

#include "entityx/Entity.h"

class ICreatable
{
public:

	virtual ~ICreatable() {}

	virtual void create(entityx::Entity entity) = 0;
};

/*TODO: Remove if not using later on*/
typedef std::shared_ptr<ICreatable> ICreatableSP;