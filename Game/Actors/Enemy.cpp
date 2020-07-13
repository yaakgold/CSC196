#include "Enemy.h"
#include <fstream>
#include <Math\MathFile.h>

bool Enemy::Load(const std::string& fileName)
{
    bool success = false;

    std::ifstream stream(fileName);
    if (stream.is_open())
    {
        success = true;

        //Load Actor
        Actor::Load(stream);

        //Load Thrust
        std::string line;
        std::getline(stream, line);
        m_thrust = std::stof(line);

        stream.close();
    }

    return success;
}

void Enemy::Update(float dt)
{
    Vector2 direction = m_target->GetTransform().position - m_transform.position;
    Vector2 velocity = direction.Normalized() * speed;
    m_transform.position += velocity * dt;
    m_transform.angle = std::atan2(direction.y, direction.x) + DegsToRads(90);

}
