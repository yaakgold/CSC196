#pragma once
#include <Object\Actor.h>
#include "Math/Random.h"

using namespace hummus;

class Enemy : public Actor
{
public:
	Enemy() { int cf = random(0, 2); canFire = cf; }

	virtual eType GetType() { return eType::ENEMY; }

	virtual bool Load(const std::string& fileName) override;

	virtual void Update(float dt) override;

	virtual void OnCollision(Actor* collision);

	void SetTarget(Actor* actor) { m_target = actor; }
	void SetThrust(float thrust) { m_thrust = thrust; }

	bool GetActive() { return isActive; }

protected:
	float m_thrust{ 0.0f };
	Actor* m_target{ nullptr };
	float m_rotSpeed{ 0 };

	float fireRate{ random(2, 4) };
	float fireTimer{ 0.0f };

	bool canFire{ false };
	bool isActive{ true };
	float waitTime{ 2.0f };
};
