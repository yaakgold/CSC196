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

    void Actor::Update(float dt)
    {

    }

    void Actor::Draw(Core::Graphics& graphics)
    {
        m_shape.Draw(graphics, m_transform);
    }
}

