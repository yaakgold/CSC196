#pragma once
#include <Object\Actor.h>

using namespace hummus;

namespace game
{
	class Player : public Actor
	{
	public:
		virtual bool Load(const std::string& fileName) override;

		virtual void Update(float dt) override;

	protected:
		float thrust;
		float rotSpeed;
		Vector2 velocity;
	};

}