#pragma once
#include <Object\Actor.h>

using namespace hummus;

namespace game
{
	class Projectile : public Actor
	{
	public:
		virtual eType GetType() { return eType::PROJECTILE; }

		virtual bool Load(const std::string& fileName) override;

		virtual void Update(float dt) override;

		virtual void OnCollision(Actor* collision);

		void SetThrust(float thrust) { m_thrust = thrust; }

	protected:
		float m_thrust{ 0.0f };
		float m_rotSpeed{ 0 };
	};

}

