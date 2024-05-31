#include "Game.hpp"
#include "Character.hpp"
#include "Map.hpp"

//Конструктор
Game::Game() : game_status(START), fov_radius(10), create_fov(true)
{
    setlocale(LC_ALL, "Russian");
	TCODConsole::initRoot(80,50,"libtcod C++ tutorial",false);
    player = new Character(40,25,'i',"Профессор", TCODColor::sky);
    characters.push(player);
    map = new Map(80,45);
}

//Деконстуктор
Game::~Game()
{
    characters.clearAndDelete();
    delete map;
}

//Функции
void Game::update()
{
    TCOD_key_t key;
    if (game_status == START) map->create_fov();
    game_status = EMPTY;
    if (game_status == NEW_TURN) {
        for (Character** iterator = characters.begin(); iterator != characters.end();
            iterator++) {
            Character* character = *iterator;
            if (character != player) {
                character->update();
            }
        }
    }
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
    int dx = 0, dy = 0;
    switch (key.vk)
    {
    case TCODK_UP: 
        dy -= 1;
        if (!map->is_wall(player->x, player->y - 1))
        {
            player->y--;
            create_fov = true;
        }
        break;
    case TCODK_DOWN: 
        dy += 1;
        if (!map->is_wall(player->x, player->y+1))
        {
            player->y++;
            create_fov = true;
        }
        break;
    case TCODK_LEFT: 
        dx -= 1;
        if (!map->is_wall(player->x - 1, player->y))
        {
            player->x--;
            create_fov = true;
        }
        break;
    case TCODK_RIGHT: 
        dx += 1;
        if (!map->is_wall(player->x + 1, player->y)) 
        {
            player->x++;
            create_fov = true;
        }
        break;
        if (dx != 0 || dy != 0)
        {
            game_status = NEW_TURN;
            if (player->move_attack(player->x + dx, player->y + dy))
            {
                map->create_fov();
            }
        }
    default:break;
    };
    if (create_fov)
    {
        map->create_fov();
        create_fov = false;
    }
}

void Game::render()
{
    TCODConsole::root->clear();
    // draw the map
    map->render();
    // draw the actors
    for (Character** iterator = characters.begin(); iterator != characters.end(); iterator++) 
    {
        Character* character = *iterator;
        if (map->is_in_Fov(character->x, character->y))
        {
            character->render();
        }
    }
}