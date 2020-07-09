#include "core.h"
#include "Math/MathFile.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include "Math/Transform.h"
#include "Graphics/Shape.h"
#include "Object/Actor.h"
#include <string>
#include <iostream>

using namespace hummus;

float speed = 350;
float rotSpeed = 3;

float t{ 0 };

float frameTime;
float roundTime{ 0 };
bool gameOver{ false };

DWORD prevTime, deltaTime;

Actor player;

Actor enemy;

bool Update(float dt)
{
    DWORD time = GetTickCount();
    deltaTime = time - prevTime;
    prevTime = time;
    
    t += (dt * 5.0f);
    
    frameTime = dt;
    roundTime += dt;

    if (roundTime >= 5.0f) gameOver = true;

    //if (gameOver) dt = 0.0f;
    
    //dt *= 2.0f;

    bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

    int x, y;
    Core::Input::GetMousePos(x, y);

    //Vector2 target = Vector2(x, y);
    //Vector2 direction = target - position;

    Vector2 force;

    if (Core::Input::IsPressed(Core::Input::KEY_UP) || Core::Input::IsPressed('W')) { force = Vector2::forward * speed * dt; }
    if (Core::Input::IsPressed(Core::Input::KEY_DOWN) || Core::Input::IsPressed('S')) { force = Vector2::forward * -speed * dt; }

    Vector2 direction = force;
    direction = Vector2::Rotate(direction, player.GetTransform().angle);
    player.GetTransform().position += direction;

    if (Core::Input::IsPressed(Core::Input::KEY_LEFT) || Core::Input::IsPressed('A')) { player.GetTransform().angle -= dt * rotSpeed; }
    if (Core::Input::IsPressed(Core::Input::KEY_RIGHT) || Core::Input::IsPressed('D')) { player.GetTransform().angle += dt * rotSpeed; }

    player.GetTransform().position = Clamp(player.GetTransform().position, { 0, 0 }, { 800, 600 });

    //if (Core::Input::IsPressed(Core::Input::KEY_LEFT) || Core::Input::IsPressed('A')) { position += Vector2::left * speed * dt; }
    //if (Core::Input::IsPressed(Core::Input::KEY_RIGHT) || Core::Input::IsPressed('D')) { position += Vector2::right * speed * dt; }
    
    return quit;
}

void Draw(Core::Graphics& graphics)
{
    graphics.SetColor(Color(1, 1, 1));
    graphics.DrawString(10, 10, std::to_string(frameTime).c_str());
    graphics.DrawString(10, 30, std::to_string(1.0f / frameTime).c_str());
    graphics.DrawString(10, 50, std::to_string(deltaTime / 1000.0f).c_str());

    float v = (std::sin(t) + 1.0f) * 0.5f;

    Vector2 p = Lerp(Vector2{ 400, 300 }, Vector2{ 600, 0 }, v);
    Color c = Lerp(Color{ 0, 0, 1}, Color{1, 0, 0 }, v);
    graphics.SetColor(c);
    graphics.DrawString(p.x, p.y, "Title or something like that");

    if (gameOver) graphics.DrawString(400, 300, "Game Over");

    player.Draw(graphics);
    enemy.Draw(graphics);
}

int main()
{
    prevTime = GetTickCount();

    player.Load("player.txt");
    enemy.Load("enemy.txt");

    char name[] = "CSC196"; 
    Core::Init(name, 800, 600); 
    Core::RegisterUpdateFn(Update);
    Core::RegisterDrawFn(Draw); 

    Core::GameLoop();
    Core::Shutdown();
}