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

}

