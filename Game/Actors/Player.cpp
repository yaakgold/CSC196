#include "Player.h"
#include <fstream>

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
    Vector2 force;

    if (Core::Input::IsPressed(Core::Input::KEY_UP) || Core::Input::IsPressed('W')) { force = Vector2::forward * thrust; }
    if (Core::Input::IsPressed(Core::Input::KEY_DOWN) || Core::Input::IsPressed('S')) { force = Vector2::forward * -thrust; }
    force = Vector2::Rotate(force, m_transform.angle);

    //Gravity
    //force += Vector2{ 0, 200 };

    velocity += force * dt;
    velocity *= .99f;

    m_transform.position += velocity * dt;

    //Rotate
    if (Core::Input::IsPressed(Core::Input::KEY_LEFT) || Core::Input::IsPressed('A')) { m_transform.angle -= dt * rotSpeed; }
    if (Core::Input::IsPressed(Core::Input::KEY_RIGHT) || Core::Input::IsPressed('D')) { m_transform.angle += dt * rotSpeed; }

    //Screen wrapping
    if (m_transform.position.x > 800) m_transform.position.x = 0;
    if (m_transform.position.x < 0) m_transform.position.x = 800;

    if (m_transform.position.y < 0) m_transform.position.y = 600;
    if (m_transform.position.y > 600) m_transform.position.y = 0;

}