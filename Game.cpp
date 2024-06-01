#include "Game.hpp"
#include "Map.hpp"
#include "Character.hpp"

//Конструктор
Game::Game(int screen_width, int screen_height) : game_status(START), fov_radius(10), create_fov(true), screen_width(screen_width), screen_height(screen_height)
{
    TCODConsole::initRoot(screen_width, screen_height, "Game project", false);
    setlocale(LC_ALL, "Russian");
    player = new Character(40,25,'i',"Профессор", TCODColor::sky);
    player->target=new Player_Target(50, 5);
    player->target->current_hp = player->target->max_hp;
    player->attacker = new Attacker(10);
    player->ai = new Player_ai();
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
void Game::go_background(Character* character) //Убирает умершего врага на задний фон, чтобы мы видели героя над ним
{
    characters.remove(character);
    characters.insertBefore(character, 0);
}

void Game::update()
{
    if (game_status == START) map->create_fov();

    for (Character** iterator = characters.begin(); iterator != characters.end();
        iterator++) {
        Character* character = *iterator;
        if (character != player) 
        {
            character->update();
        }
    }
 
    TCOD_key_t key;
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
    switch (key.vk)
    {
    case TCODK_UP: 
        if (!map->is_wall(player->x, player->y - 1) && map->can_walk(player->x, player->y - 1))
        {
            player->y--;
            create_fov = true;
        }
        break;
    case TCODK_DOWN: 
        if (!map->is_wall(player->x, player->y+1) && map->can_walk(player->x, player->y + 1))
        {
            player->y++;
            create_fov = true;
        }
        break;
    case TCODK_LEFT: 
        if (!map->is_wall(player->x - 1, player->y) && map->can_walk(player->x - 1, player->y))
        {
            player->x--;
            create_fov = true;
        }
        break;
    case TCODK_RIGHT: 
        if (!map->is_wall(player->x + 1, player->y) && map->can_walk(player->x + 1, player->y))
        {
            player->x++;
            create_fov = true;
        }
        break;
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
    player->render();
    TCODConsole::root->printf(1, screen_height - 2, "HP : %d/%d",(int)player->target->current_hp, (int)player->target->max_hp);
}