#include "Enemy.h"
#include "Graphics/ParticleSystem.h"
#include "Object/Scene.h"
#include "../Game.h"
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
    Vector2 velocity = direction.Normalized() * m_thrust;
    m_transform.position += velocity * dt;
    m_transform.angle = (std::atan2(direction.y, direction.x) + DegsToRads(90)) - (dt * m_rotSpeed);

    m_transform.Update();
}

void Enemy::OnCollision(Actor* collision)
{
    if (collision->GetType() == eType::PROJECTILE)
    {
        m_destroy = true;

        //Set Game Score
        m_scene->GetGame()->AddScore(100);

        Color colors[] = { Color::white, Color::blue, Color::yellow, Color::red, Color::green };
        Color color = colors[rand() % 5];

        g_particleSystem.Create(m_transform.position, 0, 180, 30, color, 1, 100, 200);
    }
}

