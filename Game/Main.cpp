#include "core.h"
#include "Game.h"
#include <time.h>
#include "Audio/AudioSystem.h"

Game g;

bool Update(float dt)
{
    return g.Update(dt);
}

void Draw(Core::Graphics& graphics)
{
    g.Draw(graphics);
}

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));

    g_audioSystem.Startup();
    g.Startup();

    char name[] = "CSC196"; 
    Core::Init(name, Game::WIDTH, Game::HEIGHT); 
    Core::RegisterUpdateFn(Update);
    Core::RegisterDrawFn(Draw); 

    Core::GameLoop();
    Core::Shutdown();

    g.Shutdown();
    g_audioSystem.Shutdown();

    return 0;
}