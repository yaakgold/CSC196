#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include <iostream>

const size_t NUM_POINTS = 40;
float speed = 5;
float scale = 1;
std::vector< hum::Vector2> points;
hum::Vector2 position{ 400.0f, 300.0f };


bool Update(float dt)
{
    bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

    int x, y;
    Core::Input::GetMousePos(x, y);

    hum::Vector2 target = hum::Vector2(x, y);
    hum::Vector2 direction = target - position;

    position += direction.Normalized() * speed;

    //if (Core::Input::IsPressed(Core::Input::KEY_LEFT) || Core::Input::IsPressed('A')) { position += hum::Vector2{ -1.0f, 0.0f } * speed; }
    //if (Core::Input::IsPressed(Core::Input::KEY_RIGHT) || Core::Input::IsPressed('D')) { position += hum::Vector2{ 1.0f, 0.0f } * speed; }
    //if (Core::Input::IsPressed(Core::Input::KEY_UP) || Core::Input::IsPressed('W')) { position += hum::Vector2{ 0.0f, -1.0f } * speed; }
    //if (Core::Input::IsPressed(Core::Input::KEY_DOWN) || Core::Input::IsPressed('S')) { position += hum::Vector2{ 0.0f, 1.0f } * speed; }

    for (hum::Vector2& point : points)
    {
        point = { hum::random(-10.0f, 10.0f), hum::random(-10.0f, 10.0f) };
    }

    return quit;
}

void Draw(Core::Graphics& graphics)
{
    graphics.SetColor(RGB(rand() % 256, rand() % 256, rand() % 256));
    
    for (size_t i = 0; i < NUM_POINTS - 1; i++)
    {
        hum::Vector2 p1 = position + (points[i] * scale);
        hum::Vector2 p2 = position + (points[i + 1] * scale);

        graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
    }
}

int main()
{
    for (size_t i = 0; i < 40; i++)
    {
        points.push_back({hum::random(0.0f, 800.0f), hum::random(0.0f, 600.0f)});
    }

    char name[] = "CSC196"; 
    Core::Init(name, 800, 600); 
    Core::RegisterUpdateFn(Update); 
    Core::RegisterDrawFn(Draw); 

    Core::GameLoop();
    Core::Shutdown();
}