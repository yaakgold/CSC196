#pragma once
#include <Vector2.h>


namespace hummus
{
	struct Matrix22
	{
		float m[2][2];
		//m[0][0]; m[1][0];
		//m[0][1]; m[1][1];

		Matrix22() = default;

		Matrix22(const Vector2& col1, const Vector2& col2)
		{
			m[0][0] = col1[0]; m[1][0] = col2[0];
			m[0][1] = col1[1]; m[1][1] = col2[1];
		}

		void Scale(float s)
		{
			m[0][0] = s; m[1][0] = 0;
			m[0][1] = 0; m[1][1] = s;
		}

		void Scale(float sx, float sy)
		{
			m[0][0] = sx; m[1][0] = 0;
			m[0][1] = 0; m[1][1] = sy;
		}

		void Scale(const Vector2& v)
		{
			m[0][0] = v.x; m[1][0] = 0;
			m[0][1] = 0; m[1][1] = v.y;
		}

		void Rotate(float angle)
		{
			m[0][0] = std::cos(angle);  m[1][0] = std::sin(angle);
			m[0][1] = -std::sin(angle); m[1][1] = std::cos(angle);
		}

		void SetIdentity()
		{
			m[0][0] = 1; m[1][0] = 0;
			m[0][1] = 0; m[1][1] = 1;
		}
		
		Matrix22 operator * (const Matrix22& mat)
		{
			Matrix22 result;

			result.m[0][0] = m[0][0] * mat.m[0][0] + m[1][0] * mat.m[0][1];
			result.m[1][0] = m[0][0] * mat.m[1][0] + m[1][0] * mat.m[1][1];
			result.m[0][1] = m[0][1] * mat.m[0][0] + m[1][1] * mat.m[0][1];
			result.m[1][1] = m[0][1] * mat.m[1][0] + m[1][1] * mat.m[1][1];

			return result;
		}

		Vector2 operator * (const Vector2& v)
		{
			Vector2 result;

			result.x = v.x * m[0][0] + v.y * m[0][1];
			result.y = v.x * m[1][0] + v.y * m[1][1];

			return result;
		}

		friend Vector2 operator * (const Vector2& v, const Matrix22& mat)
		{
			Vector2 result;

			result.x = v.x * mat.m[0][0] + v.y * mat.m[0][1];
			result.y = v.x * mat.m[1][0] + v.y * mat.m[1][1];

			return result;
		}
		
		/*friend Vector2& operator *= (Vector2& v, const Matrix22& mat)
		{
			v.x = v.x * mat.m[0][0] + v.y * mat.m[0][1];
			v.y = v.x * mat.m[1][0] + v.y * mat.m[1][1];

			return v;
		}*/

	};
}