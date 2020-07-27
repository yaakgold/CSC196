#include "core.h"
#include "Game.h"
#include "Audio/AudioSystem.h"

namespace game
{
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
        g_audioSystem.Startup();
        g.Startup();

        char name[] = "CSC196"; 
        Core::Init(name, Game::WIDTH, Game::HEIGHT); 
        Core::RegisterUpdateFn(Update);
        Core::RegisterDrawFn(Draw); 

        Core::GameLoop();
        Core::Shutdown();

        g_audioSystem.Shutdown();
        g.Shutdown();

        return 0;
    }
}

int main()
{
    game::main();
}