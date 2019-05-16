#pragma once
struct AttackSpeedComponent : public entityx::Component<AttackSpeedComponent>
{
	AttackSpeedComponent(float speed) {
		this->atkSpeed = speed;
		this->timeAttack = speed;
	}
	float timeAttack;
	float atkSpeed;
};