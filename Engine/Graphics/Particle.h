#pragma once
#include "Math/Vector2.h"
#include "Math/Color.h"

namespace hummus
{
	struct Particle
	{
		Vector2 pos;
		Vector2 prevPos;
		Vector2 vel;
		Color color;
		float damping{ 0.98f };
		float lifetime;
		bool isActive{ false };
	};
}