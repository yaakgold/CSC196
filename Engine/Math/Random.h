#pragma once
#include <random>

namespace hummus
{
	float random()
	{
		return rand() / static_cast<float>(RAND_MAX);
	}
	
	float random(float min, float max)
	{
		if (min > max)
		{
			std::swap(min, max);
		}

		return min + (max - min) * random();
	}
}