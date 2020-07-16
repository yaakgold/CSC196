#pragma once
#include <Object\Actor.h>

using namespace hummus;

namespace game
{
	class Enemy : public Actor
	{
	public:
		virtual bool Load(const std::string& fileName) override;

		virtual void Update(float dt) override;

		void SetTarget(Actor* actor) { m_target = actor; }

		void SetThrust(float thrust) { m_thrust = thrust; }

	protected:
		float m_thrust{ 0.0f };
		Actor* m_target{ nullptr };
		float m_rotSpeed{ 0 };
	};

}

