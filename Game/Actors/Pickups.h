#pragma once
#include <Object\Actor.h>
#include "Math/Random.h"

using namespace hummus;

class Pickups : public Actor
{
public:
	enum class ePickup
	{
		NONE,
		RAPID_FIRE,
		LARGE_BULLET,
		SHOTGUN,
		MULTIGUN
	};
public:
	Pickups() { m_pick = static_cast<ePickup>(random(1.0f, 5.0f)); }

	virtual ~Pickups() {}

	virtual bool Load(const std::string& fileName) override;

	virtual eType GetType() { return eType::PICKUP; }
	ePickup GetPick() { return m_pick; }

	virtual void Update(float dt) override;

protected:
	ePickup m_pick;
};

