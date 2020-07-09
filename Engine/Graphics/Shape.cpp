#include "pch.h"
#include "Shape.h"
#include <fstream>

bool hummus::Shape::Load(const std::string& fileName)
{
    bool success = false;

    std::ifstream stream(fileName);
    if (stream.is_open())
    {
        success = true;

        //Read Color

        stream >> m_color;

        //Read Points
        while (!stream.eof())
        {
            Vector2 point;
            stream >> point;

            if (!stream.eof())
            {
                m_points.push_back(point);
            }
        }

        stream.close();
    }

    return success;
}

void hummus::Shape::Draw(Core::Graphics& graphics, Vector2 position, float scale, float angle)
{
    graphics.SetColor(m_color);

    for (size_t i = 0; i < m_points.size() - 1; i++)
    {
        //Local / object space points
        Vector2 p1 = m_points[i];
        Vector2 p2 = m_points[i + 1];

        //transform
        //scale
        p1 *= scale;
        p2 *= scale;

        //rotate
        p1 = Vector2::Rotate(p1, angle);
        p2 = Vector2::Rotate(p2, angle);

        //translate
        p1 += position;
        p2 += position;

        graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
    }
}

void hummus::Shape::Draw(Core::Graphics& graphics, const Transform& transform)
{
    Draw(graphics, transform.position, transform.scale, transform.angle);
}

