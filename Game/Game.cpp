#include "core.h"
#include "Math/MathFile.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include <string>
#include <iostream>

using namespace hummus;

const size_t NUM_POINTS = 5;
float speed = 350;
float rotSpeed = 3;
float scale = 4;
float angle = 0;
std::vector< Vector2> points = { { 0, -3 }, { 3, 3 }, { 0, 6 }, { -3, 3 }, { 0, -3 } };
Vector2 position{ 400.0f, 300.0f };
Color color{1, 0, 0};

Shape player;
//Shape player{ points, color };

float frameTime;
float roundTime{ 0 };
bool gameOver{ false };

DWORD prevTime, deltaTime;

bool Update(float dt)
{
    DWORD time = GetTickCount();
    deltaTime = time - prevTime;
    prevTime = time;
    
    
    frameTime = dt;
    roundTime += dt;

    if (roundTime >= 5.0f) gameOver = true;

    if (gameOver) dt = 0.0f;
    
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
    direction = Vector2::Rotate(direction, angle);
    position += direction;

    if (Core::Input::IsPressed(Core::Input::KEY_LEFT) || Core::Input::IsPressed('A')) { angle -= dt * rotSpeed; }
    if (Core::Input::IsPressed(Core::Input::KEY_RIGHT) || Core::Input::IsPressed('D')) { angle += dt * rotSpeed; }

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

    if (gameOver) graphics.DrawString(400, 300, "Game Over");

    player.Draw(graphics, position, scale, angle);
}

int main()
{
    prevTime = GetTickCount();

    player.Load("ship.txt");
    player.SetColor(color);

    char name[] = "CSC196"; 
    Core::Init(name, 800, 600); 
    Core::RegisterUpdateFn(Update); 
    Core::RegisterDrawFn(Draw); 

    Core::GameLoop();
    Core::Shutdown();
}