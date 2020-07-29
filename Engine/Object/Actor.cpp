#include "pch.h"
#include "Actor.h"
#include <fstream>

namespace hummus
{
    bool Actor::Load(const std::string& fileName)
    {
        bool success = false;

        std::ifstream stream(fileName);
        if (stream.is_open())
        {
            success = true;

            //Transform
            stream >> m_transform;

            //Shape Name
            std::string shapename;
            stream >> shapename;

            //Shape
            m_shape.Load(shapename);

            stream.close();
        }

        return success;
    }

    void Actor::Load(std::istream& stream)
    {
        stream >> m_transform;

        std::string shapeName;
        std::getline(stream, shapeName);
        m_shape.Load(shapeName);
    }

    void Actor::Update(float dt)
    {
        //Screen wrapping
        if (m_transform.position.x > 800) m_transform.position.x = 0;
        if (m_transform.position.x < 0) m_transform.position.x = 800;

        if (m_transform.position.y < 0) m_transform.position.y = 600;
        if (m_transform.position.y > 600) m_transform.position.y = 0;
    }

    void Actor::Draw(Core::Graphics& graphics)
    {
        m_shape.Draw(graphics, m_transform);
    }

    float Actor::GetRadius()
    {
        return m_shape.GetRadius() * m_transform.scale;
    }

    void Actor::AddChild(Actor* child)
    {
        child->m_parent = this;
        m_children.push_back(child);
    }

    void Actor::Destroy()
    {
        for (auto child : m_children)
        {
            delete child;
        }
        m_children.clear();
    }
}

