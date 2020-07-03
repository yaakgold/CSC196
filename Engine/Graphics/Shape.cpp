#include "pch.h"
#include "Shape.h"

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