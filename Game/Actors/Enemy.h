#pragma once
#include <Object\Actor.h>

using namespace hummus;

class Enemy : public Actor
{
public:
	virtual eType GetType() { return eType::ENEMY; }

	virtual bool Load(const std::string& fileName) override;

	virtual void Update(float dt) override;

	virtual void OnCollision(Actor* collision);

	void SetTarget(Actor* actor) { m_target = actor; }

	void SetThrust(float thrust) { m_thrust = thrust; }

protected:
	float m_thrust{ 0.0f };
	Actor* m_target{ nullptr };
	float m_rotSpeed{ 0 };
};
