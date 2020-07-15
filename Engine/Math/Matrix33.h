#pragma once

#pragma once
#include "Vector2.h"


namespace hummus
{
	struct Matrix33
	{
		float m[3][3];
		//m[0][0]; m[1][0]; m[2][0];
		//m[0][1]; m[1][1]; m[2][1];
		//m[0][2]; m[1][2]; m[2][2];

		void Scale(float s)
		{
			m[0][0] = s;	m[1][0] = 0;	m[2][0] = 0;
			m[0][1] = 0;	m[1][1] = s;	m[2][1] = 0;
			m[0][2] = 0;	m[1][2] = 0;	m[2][2] = 1;
		}

		void Scale(float sx, float sy)
		{
			m[0][0] = sx;	m[1][0] = 0;	m[2][0] = 0;
			m[0][1] = 0;	m[1][1] = sy;	m[2][1] = 0;
			m[0][2] = 0;	 m[1][2] = 0;	m[2][2] = 1;
		}

		void Scale(const Vector2& v)
		{
			m[0][0] = v.x;	m[1][0] = 0;	m[2][0] = 0;
			m[0][1] = 0;	m[1][1] = v.y;	m[2][1] = 0;
			m[0][2] = 0;	m[1][2] = 0;	m[2][2] = 1;
		}

		void Rotate(float angle)
		{
			m[0][0] = std::cos(angle);		m[1][0] = std::sin(angle);	m[2][0] = 0;
			m[0][1] = -std::sin(angle);		m[1][1] = std::cos(angle);	m[2][1] = 0;
			m[0][2] = 0;					m[1][2] = 0;				m[2][2] = 1;
		}

		void SetIdentity()
		{
			m[0][0] = 1;	m[1][0] = 0;	m[2][0] = 0;
			m[0][1] = 0;	m[1][1] = 1;	m[2][1] = 0;
			m[0][2] = 0;	m[1][2] = 0;	m[2][2] = 1;
		}						

		void Translate(const Vector2& v)
		{
			m[0][0] = 1;	m[1][0] = 0;	m[2][0] = 0;
			m[0][1] = 0;	m[1][1] = 1;	m[2][1] = 0;
			m[0][2] = v.x;	m[1][2] = v.y;	m[2][2] = 1;
		}

		Matrix33 operator * (const Matrix33& mat)
		{
			Matrix33 result;

			result.m[0][0] = m[0][0] * mat.m[0][0] + m[1][0] * mat.m[0][1] + m[2][0] * mat.m[0][2];
			result.m[0][1] = m[0][1] * mat.m[0][0] + m[1][1] * mat.m[0][1] + m[2][1] * mat.m[0][2];
			result.m[0][2] = m[0][2] * mat.m[0][0] + m[1][2] * mat.m[0][1] + m[2][2] * mat.m[0][2];

			result.m[1][0] = m[0][0] * mat.m[1][0] + m[1][0] * mat.m[1][1] + m[2][0] * mat.m[1][2];
			result.m[1][1] = m[0][1] * mat.m[1][0] + m[1][1] * mat.m[1][1] + m[2][1] * mat.m[1][2];
			result.m[1][2] = m[0][2] * mat.m[1][0] + m[1][2] * mat.m[1][1] + m[2][2] * mat.m[1][2];

			result.m[2][0] = m[0][0] * mat.m[2][0] + m[1][0] * mat.m[2][1] + m[2][0] * mat.m[2][2];
			result.m[2][1] = m[0][1] * mat.m[2][0] + m[1][1] * mat.m[2][1] + m[2][1] * mat.m[2][2];
			result.m[2][2] = m[0][2] * mat.m[2][0] + m[1][2] * mat.m[2][1] + m[2][2] * mat.m[2][2];

			return result;
		}

		Vector2 operator * (const Vector2& v)
		{
			Vector2 result;

			result.x = v.x * m[0][0] + v.y * m[0][1] + m[0][2];
			result.y = v.x * m[1][0] + v.y * m[1][1] + m[1][2];

			return result;
		}

		friend Vector2 operator * (const Vector2& v, const Matrix33& mat)
		{
			Vector2 result;

			result.y = v.x * mat.m[1][0] + v.y * mat.m[1][1] + mat.m[1][2];
			result.x = v.x * mat.m[0][0] + v.y * mat.m[0][1] + mat.m[0][2];

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