#include "core.h"
#include "Math/MathFile.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include "Math/Transform.h"
#include "Graphics/Shape.h"
#include "Object/Actor.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include <string>
#include <iostream>

using namespace hummus;

float thrust = 300;
float rotSpeed = 3;

float t{ 0 };

float frameTime;
float roundTime{ 0 };
bool gameOver{ false };

DWORD prevTime, deltaTime;

Player player;
Enemy enemy;

bool Update(float dt)
{
    DWORD time = GetTickCount();
    deltaTime = time - prevTime;
    prevTime = time;
    
    t += (dt * 5.0f);
    
    frameTime = dt;

    bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

    int x, y;
    Core::Input::GetMousePos(x, y);

    player.Update(dt);
    enemy.Update(dt);
    
    return quit;
}

void Draw(Core::Graphics& graphics)
{
    graphics.SetColor(Color(1, 1, 1));
    graphics.DrawString(10, 10, std::to_string(frameTime).c_str());
    graphics.DrawString(10, 30, std::to_string(1.0f / frameTime).c_str());
    graphics.DrawString(10, 50, std::to_string(deltaTime / 1000.0f).c_str());

    if (gameOver) graphics.DrawString(400, 300, "Game Over");

    player.Draw(graphics); 
    enemy.Draw(graphics);
}

int main()
{
    prevTime = GetTickCount();

    player.Load("player.txt");
    enemy.Load("enemy.txt");
    enemy.SetTarget(&player);

    char name[] = "CSC196"; 
    Core::Init(name, 800, 600); 
    Core::RegisterUpdateFn(Update);
    Core::RegisterDrawFn(Draw); 

    Core::GameLoop();
    Core::Shutdown();
}