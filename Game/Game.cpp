#include "Game.h"
#include "Actors/Locator.h"
#include "Actors/Pickups.h"
#include "Audio/AudioSystem.h"

const int Game::WIDTH = 800;
const int Game::HEIGHT = 600;

void Game::Startup()
{
    g_particleSystem.Startup();
    m_scene.Startup();
    m_scene.SetGame(this);

    g_audioSystem.AddAudio("Laser", "Laser.wav");
    g_audioSystem.AddAudio("Explosion", "Explosion.wav");
    g_audioSystem.AddAudio("Pickup", "Pickup.wav");
    g_audioSystem.AddAudio("NoPickup", "NoPickup.wav");
    g_audioSystem.AddAudio("ESpawn", "ESpawn.wav");
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
            m_score = 0;
            m_lives = 3;
        }
        break;
    case Game::eState::START_GAME:
    {
        Player* player = new Player;
        player->Load("player.txt");

        Locator* locator = new Locator;
        locator->GetTransform().position = Vector2{ 2, 5 };
        locator->GetTransform().angle = DegsToRads(90);

        player->AddChild(locator);

        locator = new Locator;
        locator->GetTransform().position = Vector2{ -2, 5 };
        locator->GetTransform().angle = DegsToRads(90);

        player->AddChild(locator);

        m_scene.AddActor(player);

        CreatePickup();

        for (int i = 0; i < 4; i++)
        {
            Enemy* enemy = new Enemy;
            enemy->Load("enemy.txt");
            enemy->SetTarget(player);

            float dist = random(300, 600);
            float angle = random(0, TWO_PI);
            Vector2 pos = Vector2{ 400, 300 } + Vector2::Rotate({ dist, 0.0f }, angle);

            enemy->GetTransform().position = pos;
            g_particleSystem.Create(pos, 0, 180, 500, Color::white, 1, 50, 75);
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
            for (int i = 0; i < 2; i++)
            {
                Enemy* enemy = new Enemy;
                enemy->Load("enemy.txt");
                enemy->SetTarget(m_scene.GetActor<Player>());

                float dist = random(100, 200);
                float angle = random(0, TWO_PI);
                Vector2 pos = Vector2{ 400, 300 } + Vector2::Rotate({ dist, 0.0f }, angle);

                enemy->GetTransform().position = pos;
                g_particleSystem.Create(pos, 0, 180, 500, Color::white, 1, 50, 75);
                enemy->SetThrust(random(100, 150));

                m_scene.AddActor(enemy);
            }
        }
        break;
    case Game::eState::PLAYER_DEAD:
    {
        m_lives--;
        m_state = (m_lives <= 0) ? eState::GAME_OVER : eState::GAME_WAIT;
        m_stateTime = 3;
    }
        break;
    case Game::eState::GAME_WAIT:
        m_stateTime -= dt;
        if (m_stateTime <= 0)
        {
            m_scene.RemoveAllActors();
            m_state = eState::START_GAME;
        }
        break;
    case Game::eState::GAME_OVER:
        m_stateTime -= dt;
        if (m_stateTime <= 0)
        {
            m_scene.RemoveAllActors();
            m_state = eState::TITLE;
        }
        break;
    default:
        break;
    }
    
    g_audioSystem.Update(dt);
    m_scene.Update(dt);

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
        break;
    case Game::eState::GAME_OVER:
        graphics.SetColor(Color::blue);
        graphics.DrawString(400, 300, "Game Over");
        break;
    default:
        break;
    }

    graphics.SetColor(Color::white);
    graphics.DrawString(700, 10, std::to_string(m_score).c_str());
    graphics.DrawString(700, 30, ("LIVES: " + std::to_string(m_lives)).c_str());
    if(m_scene.GetActor<Player>())
        graphics.DrawString(700, 50, (m_scene.GetActor<Player>()->GetPickup() + " " + std::to_string(m_scene.GetActor<Player>()->GetPickupTimeLeft())).c_str());

    m_scene.Draw(graphics);
}

void Game::CreatePickup()
{
    Pickups* pickup = new Pickups();
    pickup->Load("pickup.txt");
    m_scene.AddActor(pickup);
}