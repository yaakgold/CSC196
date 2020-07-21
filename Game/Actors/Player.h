#pragma once
#include <Object\Actor.h>

using namespace hummus;

namespace game
{
	class Player : public Actor
	{
	public:
		virtual eType GetType() { return eType::PLAYER; }

		virtual bool Load(const std::string& fileName) override;

		virtual void Update(float dt) override;

	protected:
		float thrust;
		float rotSpeed;
		float fireRate{ 0.2f };
		float fireTimer{ 0.0f };
		Vector2 velocity;
	};

}