#include "pch.h"
#include "Transform.h"

namespace hummus
{
    std::istream& operator >> (std::istream& stream, Transform& t)
    {
        stream >> t.position;
        stream >> t.scale;
        stream >> t.angle;        

        return stream;
    }

}

