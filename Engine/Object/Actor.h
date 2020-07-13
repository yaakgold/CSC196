#pragma once

#include "Math/Transform.h"
#include "Graphics/Shape.h"

namespace hummus
{
	class Actor
	{
	public:
		Actor() {}
		Actor(const Transform& transform, const Shape& shape) : m_transform{ transform }, m_shape{ shape } {}
		virtual ~Actor() {}

		virtual bool Load(const std::string& fileName);
		virtual void Load(std::istream& stream);

		virtual void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);

		Transform& GetTransform() { return m_transform; }
		Shape& GetShape() { return m_shape; }


	protected:
		Transform m_transform;
		Shape m_shape;
	};
}