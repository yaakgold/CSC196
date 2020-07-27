#pragma once

#include "Matrix33.h"

namespace hummus
{
	struct Transform
	{
		Vector2 position;
		float scale;
		float angle;

		Matrix33 matrix;

		Transform() : position{ 0, 0 }, scale{ 1 }, angle{ 0 } {}
		Transform(const Vector2& pos, float scale = 1, float angle = 0) : position{ pos }, scale{ scale }, angle{ angle } {}

		void Update();
		void Update(const Matrix33& mat);

		//Overload methods
		//Streams
		friend std::istream& operator >> (std::istream& stream, Transform& t);
	};
}