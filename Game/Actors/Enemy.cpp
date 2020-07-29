#include "Enemy.h"
#include "Graphics/ParticleSystem.h"
#include "Object/Scene.h"
#include "Audio/AudioSystem.h"
#include "Projectile.h"
#include "../Game.h"
#include <fstream>
#include <Math\MathFile.h>
#include "Locator.h"

bool Enemy::Load(const std::string& fileName)
{
    g_audioSystem.PlayAudio("ESpawn");

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

    if (canFire)
    {
        m_shape.SetColor(Color::purple);
        m_thrust *= .5f;

        Locator* locator = new Locator;
        locator->GetTransform().position = Vector2{ 0, -13 };
        locator->GetTransform().angle = m_transform.angle;
        AddChild(locator);
    }

    return success;
}

void Enemy::Update(float dt)
{
    if (isActive)
    {
        Vector2 direction;
        if (m_target)
        {
            direction = m_target->GetTransform().position - m_transform.position;
            m_transform.angle = (std::atan2(direction.y, direction.x) + DegsToRads(90)) - (dt * m_rotSpeed);
        }

        Vector2 velocity = direction.Normalized() * m_thrust;
        m_transform.position += velocity * dt;

        if (velocity.LengthSqr() > 0)
        {
            g_particleSystem.Create(m_transform.position, m_transform.angle + PI, 20, 1, Color::orange, 1, 100, 200);
        }

        m_transform.Update();

        fireTimer += dt;

        if (m_target && canFire)
        {
            if (fireTimer >= fireRate)
            {
                fireTimer = 0;
                fireRate = random(2, 4);
                Projectile* proj = new Projectile(eType::EPROJECTILE);
                proj->Load("eProjectile.txt");
                proj->GetTransform().position = m_children[0]->GetTransform().matrix.GetPosition();
                proj->GetTransform().angle = m_children[0]->GetTransform().matrix.GetAngle();
                m_scene->AddActor(proj);
            }
        }

        for (auto child : m_children)
        {
            child->Update(dt);
        }

        Actor::Update(dt);
    }

    waitTime -= dt;
    isActive = (waitTime <= 0);
}

void Enemy::OnCollision(Actor* collision)
{
    if (collision->GetType() == eType::PROJECTILE)
    {
        m_destroy = true;

        //Set Game Score
        m_scene->GetGame()->AddScore(100 * (canFire + 1));

        g_audioSystem.PlayAudio("Explosion");
        g_particleSystem.Create(m_transform.position, 0, 180, 30, m_shape.GetColor(), 1, 100, 200);
    }
}

