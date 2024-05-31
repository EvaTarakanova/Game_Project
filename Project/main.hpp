#include "Game.hpp"
#include <iostream>
#include "libtcod.hpp"
#include <stdio.h>
#include "Map.hpp"
class Actor;
#include "Character.hpp"
//#include "Attacker.hpp"
//#include "Target.hpp"
//#include "Ai.hpp"

Game game;

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