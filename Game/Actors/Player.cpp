#include "Player.h"
#include "Projectile.h"
#include "Object/Scene.h"
#include "../Game.h"
#include "Graphics/ParticleSystem.h"
#include "Audio/AudioSystem.h"
#include <fstream>
#include <Math\MathFile.h>


bool Player::Load(const std::string& fileName)
{
    bool success = false;

    std::ifstream stream(fileName);
    if (stream.is_open())
    {
        success = true;

        //Load Actor
        Actor::Load(stream);

        //Load thrust
        std::string line;
        std::getline(stream, line);
        thrust = std::stof(line);

        //Load Rotation Rate
        std::getline(stream, line);
        rotSpeed = std::stof(line);

        stream.close();
    }

    return success;
}

void Player::Update(float dt)
{
    fireTimer += dt;

    if (currentUpgrade != Pickups::ePickup::NONE)
    {
        timeWithPickup += dt;

        if (timeWithPickup >= pickupTime)
        {
            g_audioSystem.PlayAudio("NoPickup");
            DeactivatePickup();
            m_scene->GetGame()->CreatePickup();
        }
    }

    if (Core::Input::IsPressed(VK_SPACE) && fireTimer >= fireRate)
    {
        fireTimer = 0;

        float offset{ m_transform.angle };
        for (size_t i = 0; i < numBullets; i++)
        {
            if (numBullets == 4)//This is the multigun mode
            {
                offset += PI * .5f;
            }
            else if (numBullets > 1)//This means shutgund
            {
                offset -= DegsToRads((i * 3) - (PI * 2.5));
            }

            g_audioSystem.PlayAudio("Laser");
            Projectile* proj = new Projectile;
            proj->Load("projectile.txt");
            proj->GetTransform().position = m_transform.position;
            proj->GetTransform().angle = offset;
            proj->GetTransform().scale *= scaleMult;
            m_scene->AddActor(proj);
        }
    }


    Vector2 force;

    if (Core::Input::IsPressed(Core::Input::KEY_UP) || Core::Input::IsPressed('W')) { force = Vector2::forward * thrust; }
    if (Core::Input::IsPressed(Core::Input::KEY_DOWN) || Core::Input::IsPressed('S')) { force = Vector2::forward * -thrust; }
    force = Vector2::Rotate(force, m_transform.angle);

    //Gravity
    //force += Vector2{ 0, 200 };

    velocity = ((velocity + (force * dt)).Length() > maxSpeed) ? velocity : velocity + (force * dt);
    velocity *= .99f;

    m_transform.position += velocity * dt;

    //Rotate
    if (Core::Input::IsPressed(Core::Input::KEY_LEFT) || Core::Input::IsPressed('A')) { m_transform.angle -= dt * rotSpeed; }
    if (Core::Input::IsPressed(Core::Input::KEY_RIGHT) || Core::Input::IsPressed('D')) { m_transform.angle += dt * rotSpeed; }

    if (force.LengthSqr() > 0)
    {
        Actor* locator = m_children[0];
        g_particleSystem.Create(locator->GetTransform().matrix.GetPosition(), locator->GetTransform().matrix.GetAngle() + PI * .5f, 20, 1, Color::orange, 1, 100, 200);

        locator = m_children[1];
        g_particleSystem.Create(locator->GetTransform().matrix.GetPosition(), locator->GetTransform().matrix.GetAngle() + PI * .5f, 20, 1, Color::orange, 1, 100, 200);
    }

    m_transform.Update();

    for (auto child : m_children)
    {
        child->Update(dt);
    }

    Actor::Update(dt);

}

void Player::OnCollision(Actor* collision)
{
    if (collision->GetType() == eType::ENEMY)
    {
        if (dynamic_cast<Enemy*>(collision)->GetActive())
        {
            m_scene->GetGame()->SetState(Game::eState::PLAYER_DEAD);
            m_destroy = true;

            auto enemies = m_scene->GetActors<Enemy>();

            for (Enemy* e : enemies)
            {
                e->SetTarget(nullptr);
            }

            g_audioSystem.PlayAudio("Explosion");
            g_particleSystem.Create(m_transform.position, 0, 180, 30, m_shape.GetColor(), 1, 100, 200);
        }
    }

    if (collision->GetType() == eType::EPROJECTILE)
    {
        m_scene->GetGame()->SetState(Game::eState::PLAYER_DEAD);
        m_destroy = true;

        auto enemies = m_scene->GetActors<Enemy>();

        for (Enemy* e : enemies)
        {
            e->SetTarget(nullptr);
        }

        g_audioSystem.PlayAudio("Explosion");
        g_particleSystem.Create(m_transform.position, 0, 180, 30, m_shape.GetColor(), 1, 100, 200);
    }

    if (collision->GetType() == eType::PICKUP)
    {
        DeactivatePickup();
        ActivatePickup(dynamic_cast<Pickups*>(collision)->GetPick());

        collision->SetDestroy(true);

        g_audioSystem.PlayAudio("Pickup");
        g_particleSystem.Create(collision->GetTransform().position, 0, 180, 30, collision->GetShape().GetColor(), 1, 100, 200);
    }
}

std::string Player::GetPickup()
{
    switch (currentUpgrade)
    {
    case Pickups::ePickup::NONE:
        return "None";
        break;
    case Pickups::ePickup::RAPID_FIRE:
        return "Rapid Fire";
        break;
    case Pickups::ePickup::LARGE_BULLET:
        return "Large Bullet";
        break;
    case Pickups::ePickup::SHOTGUN:
        return "Shotgun";
        break;
    case Pickups::ePickup::MULTIGUN:
        return "Multigun";
        break;
    default:
        break;
    }
}

float Player::GetPickupTimeLeft()
{
    return pickupTime - timeWithPickup;
}

void Player::ActivatePickup(Pickups::ePickup newPickup)
{
    //Deactivate pickup
    DeactivatePickup();

    currentUpgrade = newPickup;

    switch (currentUpgrade)
    {
    case Pickups::ePickup::RAPID_FIRE:
        fireRate *= .5f;
        break;
    case Pickups::ePickup::LARGE_BULLET:
        scaleMult *= 2;
        break;
    case Pickups::ePickup::SHOTGUN:
        fireRate *= 2;
        numBullets = 8;
        break;
    case Pickups::ePickup::MULTIGUN:
        numBullets = 4;
        break;
    default:
        break;
    }
}

void Player::DeactivatePickup()
{
    switch (currentUpgrade)
    {
    case Pickups::ePickup::RAPID_FIRE:
        fireRate *= 2.0f;
        break;
    case Pickups::ePickup::LARGE_BULLET:
        scaleMult *= .5f;
        break;
    case Pickups::ePickup::SHOTGUN:
        fireRate *= .5f;
        numBullets = 1;
        break;
    case Pickups::ePickup::MULTIGUN:
        numBullets = 1;
        break;
    default:
        break;
    }

    timeWithPickup = 0;

    currentUpgrade = Pickups::ePickup::NONE;
}
