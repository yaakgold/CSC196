#include "pch.h"
#include "Transform.h"

namespace hummus
{
    std::istream& operator >> (std::istream& stream, Transform& t)
    {
        stream >> t.position;

        std::string line;

        std::getline(stream, line);
        t.scale = stof(line);

        std::getline(stream, line);
        t.angle = std::stof(line);

        return stream;
    }

    void Transform::Update()
    {
        Matrix33 mxScale;
        mxScale.Scale(scale);

        Matrix33 mxAngle;
        mxAngle.Rotate(angle);

        Matrix33 mxTranslate;
        mxTranslate.Translate(position);

        matrix = mxScale * mxAngle * mxTranslate;

    }

}

