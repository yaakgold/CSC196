#include "Game.h"

const int Game::WIDTH = 800;
const int Game::HEIGHT = 600;

void Game::Startup()
{
    g_particleSystem.Startup();
    m_scene.Startup();
    m_scene.SetGame(this);
}

void Game::Shutdown()
{
    m_scene.Shutdown();
    g_particleSystem.Shutdown();
}

bool Game::Update(float dt)
{
    m_frameTime = dt;

    bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

    switch (m_state)
    {
    case Game::eState::INIT:
        break;
    case Game::eState::TITLE:
        if (Core::Input::IsPressed(VK_SPACE))
        {
            m_state = eState::START_GAME;
        }
        break;
    case Game::eState::START_GAME:
    {
        Player* player = new Player;
        player->Load("player.txt");
        m_scene.AddActor(player);

        for (int i = 0; i < 10; i++)
        {
            Enemy* enemy = new Enemy;
            enemy->Load("enemy.txt");
            enemy->SetTarget(player);
            enemy->GetTransform().position = Vector2{ random(0, WIDTH), random(0, HEIGHT) };
            enemy->SetThrust(random(100, 150));
            m_scene.AddActor(enemy);
        }
        m_state = eState::GAME;
    }
        break;
    case Game::eState::GAME:
        m_spawnTime += dt;
        if (m_spawnTime >= 3)
        {
            m_spawnTime = 0;
            Enemy* enemy = new Enemy;
            enemy->Load("enemy.txt");
            enemy->SetTarget(m_scene.GetActor<Player>());
            enemy->GetTransform().position = Vector2{ random(0, WIDTH), random(0, HEIGHT) };
            enemy->SetThrust(random(100, 150));
            m_scene.AddActor(enemy);
        }
        m_scene.Update(dt);
        break;
    case Game::eState::GAME_OVER:
        break;
    default:
        break;
    }

    if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
    {
        int x, y;
        Core::Input::GetMousePos(x, y);

        Color colors[] = { Color::white, Color::blue, Color::yellow, Color::red, Color::green };
        Color color = colors[rand() % 5];

        g_particleSystem.Create({ x, y }, 0, 180, 30, color, 1, 100, 200);
    }

    g_particleSystem.Update(dt);

	return quit;
}

void Game::Draw(Core::Graphics& graphics)
{
    graphics.SetColor(Color(1, 1, 1));
    graphics.DrawString(10, 10, std::to_string(1.0f / m_frameTime).c_str());

    g_particleSystem.Draw(graphics);

    switch (m_state)
    {
    case Game::eState::INIT:
        break;
    case Game::eState::TITLE:
        graphics.SetColor(Color::purple);
        graphics.DrawString(400, 300, "Game Name Here");
        break;
    case Game::eState::START_GAME:
        break;
    case Game::eState::GAME:
        m_scene.Draw(graphics);

        graphics.SetColor(Color::white);
        graphics.DrawString(700, 10, std::to_string(m_score).c_str());
        break;
    case Game::eState::GAME_OVER:
        graphics.SetColor(Color::blue);
        graphics.DrawString(400, 300, "Game Over");
        break;
    default:
        break;
    }

}

