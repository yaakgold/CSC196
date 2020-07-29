#include "Pickups.h"
#include "Math/Random.h"
#include <fstream>

bool Pickups::Load(const std::string& fileName)
{
    bool success = false;

    std::ifstream stream(fileName);
    if (stream.is_open())
    {
        success = true;

        //Load Actor
        Actor::Load(stream);

        stream.close();
    }

    m_transform.position = { random(0, 800), random(0, 600) };

    return success;
}

void Pickups::Update(float dt)
{
    m_transform.Update();
}
