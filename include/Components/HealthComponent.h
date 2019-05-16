#pragma once
//EntityX
#include <EntityX/entityx.h>
struct HealthComponent : public entityx::Component<HealthComponent>
{
	HealthComponent(int maxHp) {
		this->maxHp = maxHp;
		this->currentHp = maxHp;
	}
	int currentHp;
	int maxHp;
};