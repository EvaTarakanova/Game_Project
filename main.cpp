#include "main.hpp"

Game game(80, 50);

int main()
{
    while (!TCODConsole::isWindowClosed())
    {
        game.update();
        game.render();
        TCODConsole::flush();
    }
    return 0;
}