#include "Projectile.h"
#include "Graphics/ParticleSystem.h"
#include <fstream>
#include <Math\MathFile.h>

bool Projectile::Load(const std::string& fileName)
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

void Projectile::Update(float dt)
{
    m_lifetime -= dt;
    if (m_lifetime <= 0) m_destroy = true;

    Vector2 direction = Vector2::Rotate(Vector2::forward, m_transform.angle);
    Vector2 velocity = direction * m_thrust;
    m_transform.position += velocity * dt;

    g_particleSystem.Create(m_transform.position, m_transform.angle + PI, 10, 1, Color::white, .5f, 100, 200);

    m_transform.Update();

    Actor::Update(dt);
}

void Projectile::OnCollision(Actor* collision)
{
    if (collision->GetType() == eType::ENEMY || (GetType() == eType::EPROJECTILE && collision->GetType() == eType::PLAYER))
    {
        m_destroy = true;
    }
}