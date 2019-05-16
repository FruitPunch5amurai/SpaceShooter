#pragma once
//EntityX
#include <EntityX/entityx.h>
struct DamageComponent : public entityx::Component<DamageComponent>
{
	DamageComponent(int damage) {
		this->damage = damage;
	}
	int damage;
};