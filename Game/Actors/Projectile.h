#pragma once
#include <Object\Actor.h>

using namespace hummus;

class Projectile : public Actor
{
public:
	Projectile() { m_type = eType::PROJECTILE; }
	Projectile(eType type) { m_type = type; }

	virtual eType GetType() { return m_type; }

	virtual bool Load(const std::string& fileName) override;

	virtual void Update(float dt) override;

	virtual void OnCollision(Actor* collision);

	void SetThrust(float thrust) { m_thrust = thrust; }

protected:
	float m_thrust{ 0.0f };
	float m_rotSpeed{ 0 };
	float m_lifetime{ 1.5f };

	eType m_type;
};

