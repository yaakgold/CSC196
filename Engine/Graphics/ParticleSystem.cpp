#include "pch.h"
#include "ParticleSystem.h"
#include "Math/Random.h"
#include "Math/MathFile.h"

using namespace hummus;

void ParticleSystem::Startup()
{
    m_particles = new Particle[300];
    m_size = 300;
}

void ParticleSystem::Shutdown()
{
    delete[] m_particles;
}

void ParticleSystem::Update(float dt)
{
    for (size_t i = 0; i < m_size; i++)
    {
        Particle* p = &m_particles[i];
        if (p->isActive)
        {
            p->lifetime -= dt;
            p->isActive = (p->lifetime > 0);

            p->prevPos = p->pos;
            p->pos += p->vel * dt;

            p->vel -= p->damping;
        }
    }
}

void ParticleSystem::Draw(Core::Graphics& graphics)
{
    for (size_t i = 0; i < m_size; i++)
    {
        Particle* p = &m_particles[i];
        if (p->isActive)
        {
            graphics.SetColor(p->color);
            graphics.DrawLine(p->pos.x, p->pos.y, p->prevPos.x, p->prevPos.y);
        }
    }
}

void ParticleSystem::Create(const Vector2& position, float angle, float angleRange, size_t count, const Color& color, float lifetime, float speedMin, float speedMax)
{
    for (size_t i = 0; i < count; i++)
    {
        Particle* p = GetFreeParticle();
        if (p)
        {
            p->isActive = true;
            p->lifetime = lifetime;
            p->pos = position;
            p->color = color;

            float angleRandom = DegsToRads(random(-angleRange, angleRange));
            Vector2 direction = Vector2::Rotate(Vector2::forward, angle + angleRandom);
            p->vel = direction * random(speedMin, speedMax);
        }
    }
}

Particle* ParticleSystem::GetFreeParticle()
{
    Particle* freeParticle{ nullptr };

    for (size_t i = 0; i < m_size; i++)
    {
        Particle* p = &m_particles[i];
        if (!p->isActive)
        {
            freeParticle = p;
            break;
        }
    }

    return freeParticle;
}
