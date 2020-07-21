#include "core.h"
#include "Math/MathFile.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include "Math/Transform.h"
#include "Graphics/Shape.h"
#include "Graphics/ParticleSystem.h"
#include "Object/Actor.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Object/Scene.h"
#include <list>
#include <string>
#include <iostream>
#include <vector>

namespace game
{
    using namespace hummus;

    unsigned int width{ 800 }, height{ 600 };

    Scene scene;
    ParticleSystem pSystem;

    float frameTime;
    float spawnTime{ 0 };

    std::list<Actor*> actors;

    /*template <typename T>
    Actor* GetActor()
    {
        Actor* result{ nullptr };
        for (Actor* actor : actors)
        {
            result = dynamic_cast<T*>(actor);
            if (result) break;
        }

        return result;
    }

    template <typename T>
    std::vector<Actor*> GetActors()
    {
        std::vector<Actor*> results;
        for (Actor* actor : actors)
        {
            T* result = dynamic_cast<T*>(actor);
            if (result) results.push_back(result);
        }

        return results;
    }*/

    bool Update(float dt)
    {
        frameTime = dt;

        bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

        Player* player = scene.GetActor<Player>();
        pSystem.Create(player->GetTransform().position, player->GetTransform().angle + PI, 20, 1, Color{ 1, 1, 1 }, 1, 100, 200);

        pSystem.Update(dt);
        scene.Update(dt);

        spawnTime += dt;
        if (spawnTime >= 3)
        {
            spawnTime = 0;
            Enemy* enemy = new Enemy;
            enemy->Load("enemy.txt");
            enemy->SetTarget(scene.GetActor<Player>());
            enemy->GetTransform().position = Vector2{ random(0, width), random(0, height) };
            enemy->SetThrust(random(100, 150));
            scene.AddActor(enemy);
        }

        for (Actor* actor : actors)
        {
            actor->Update(dt);
        }
    
        return quit;
    }

    void Draw(Core::Graphics& graphics)
    {
        graphics.SetColor(Color(1, 1, 1));
        graphics.DrawString(10, 10, std::to_string(1.0f / frameTime).c_str());

        pSystem.Draw(graphics);
        scene.Draw(graphics);

    }

    int main()
    {
        scene.Startup();
        pSystem.Startup();

        Player* player = new Player;
        player->Load("player.txt");
        scene.AddActor(player);

        for (int i = 0; i < 10; i++)
        {
            Enemy* enemy = new Enemy;
            enemy->Load("enemy.txt");
            enemy->SetTarget(player);
            enemy->GetTransform().position = Vector2{ random(0, width), random(0, height) };
            enemy->SetThrust(random(100, 150));
            scene.AddActor(enemy);
        }

        char name[] = "CSC196"; 
        Core::Init(name, width, height); 
        Core::RegisterUpdateFn(Update);
        Core::RegisterDrawFn(Draw); 

        Core::GameLoop();
        Core::Shutdown();

        scene.Shutdown();
        pSystem.Shutdown();
        return 0;
    }
}

int main()
{
    game::main();
}