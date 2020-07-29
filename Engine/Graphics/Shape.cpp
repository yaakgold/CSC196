#include "pch.h"
#include "Shape.h"
#include "Math/Matrix33.h"
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

        //Get num points
        std::string line;
        std::getline(stream, line);
        size_t size = std::stoi(line);

        //Read Points
        for (size_t i = 0; i < size; i++)
        {
            Vector2 point;
            stream >> point;

            m_points.push_back(point);
        }

        stream.close();
    }

    //Get Radius
    m_radius = 0;
    for (size_t i = 0; i < m_points.size(); i++)
    {
        //Local / object space points
        Vector2 p1 = m_points[i];
        float length = p1.Length();
        if (length > m_radius) m_radius = length;   
    }  

    return success;
}

void hummus::Shape::Draw(Core::Graphics& graphics, Vector2 position, float scale, float angle)
{
    graphics.SetColor(m_color);

    Matrix33 mxScale;
    mxScale.Scale(scale);

    Matrix33 mxAngle;
    mxAngle.Rotate(angle);

    Matrix33 mxTranslate;
    mxTranslate.Translate(position);

    Matrix33 mx;
    mx = mxScale * mxAngle * mxTranslate;

    for (size_t i = 0; i < m_points.size() - 1; i++)
    {
        //Local / object space points
        Vector2 p1 = m_points[i];
        Vector2 p2 = m_points[i + 1];

        //transform
        //scale/rotate/translate
        p1 = p1 * mx;
        p2 = p2 * mx;

        graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
    }
}

void hummus::Shape::Draw(Core::Graphics& graphics, const Transform& transform)
{
    graphics.SetColor(m_color);

    for (size_t i = 0; i < m_points.size() - 1; i++)
    {
        //Local / object space points
        Vector2 p1 = m_points[i];
        Vector2 p2 = m_points[i + 1];

        //transform
        //scale/rotate/translate
        p1 = p1 * transform.matrix;
        p2 = p2 * transform.matrix;

        graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);

    }

    //Draw(graphics, transform.position, transform.scale, transform.angle);
}

