#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include <iostream>

using namespace hummus;

const size_t NUM_POINTS = 5;
float speed = 5;
float rotSpeed = 3;
float scale = 4;
float angle = 0;
std::vector< Vector2> points = { { 0, -3 }, { 3, 3 }, { 0, 1 }, { -3, 3 }, { 0, -3 } };
Vector2 position{ 400.0f, 300.0f };
Color color{1, 0, 0};


bool Update(float dt)
{
    bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

    int x, y;
    Core::Input::GetMousePos(x, y);

    Vector2 target = Vector2(x, y);
    Vector2 direction = target - position;

    //position += direction.Normalized() * speed;

    if (Core::Input::IsPressed(Core::Input::KEY_LEFT) || Core::Input::IsPressed('A')) { angle -= dt * rotSpeed; }
    if (Core::Input::IsPressed(Core::Input::KEY_RIGHT) || Core::Input::IsPressed('D')) { angle += dt * rotSpeed; }
    //if (Core::Input::IsPressed(Core::Input::KEY_UP) || Core::Input::IsPressed('W')) { position += Vector2{ 0.0f, -1.0f } * speed; }
    //if (Core::Input::IsPressed(Core::Input::KEY_DOWN) || Core::Input::IsPressed('S')) { position += Vector2{ 0.0f, 1.0f } * speed; }

    return quit;
}

void Draw(Core::Graphics& graphics)
{
    graphics.SetColor(color);
    
    for (size_t i = 0; i < points.size() - 1; i++)
    {
        //Local / object space points
        Vector2 p1 = points[i];
        Vector2 p2 = points[i + 1];

        //transform
        //scale
        p1 *= scale;
        p2 *= scale;

        //rotate
        p1 = Vector2::Rotate(p1, angle);
        p2 = Vector2::Rotate(p2, angle);

        //translate
        p1 += position;
        p2 += position;

        graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
    }
}

int main()
{
    char name[] = "CSC196"; 
    Core::Init(name, 800, 600); 
    Core::RegisterUpdateFn(Update); 
    Core::RegisterDrawFn(Draw); 

    Core::GameLoop();
    Core::Shutdown();
}