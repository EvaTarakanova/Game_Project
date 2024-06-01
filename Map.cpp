#include "Map.hpp"
#include "Character.hpp"
#include "Game.hpp"

class BspListener : public ITCODBspCallback
{
private:
    Map& map; // a map to dig
    int roomNum; // room number
    int lastx, lasty; // center of the last room
public:
    BspListener(Map& map) : map(map), roomNum(0) {}
    bool visitNode(TCODBsp* node, void* userData) 
    {
        if (node->isLeaf())
        {
            int x, y, w, h;
            // dig a room
            TCODRandom* rng = TCODRandom::getInstance();
            w = rng->getInt(ROOM_MIN_SIZE, node->w - 2);
            h = rng->getInt(ROOM_MIN_SIZE, node->h - 2);
            x = rng->getInt(node->x + 1, node->x + node->w - w - 1);
            y = rng->getInt(node->y + 1, node->y + node->h - h - 1);
            map.create_room(roomNum == 0, x, y, x + w - 1, y + h - 1);
            if (roomNum != 0) {
                // dig a corridor from last room
                map.dig(lastx, lasty, x + w / 2, lasty);
                map.dig(x + w / 2, lasty, x + w / 2, y + h / 2);
            }
            lastx = x + w / 2;
            lasty = y + h / 2;
            roomNum++;
        }
        return true;
    }
};
//Конструктор
Map::Map(int width, int height) : width(width), height(height)
{
    tiles = new Tile[width * height];
    map = new TCODMap(width, height);
    TCODBsp bsp(0, 0, width, height);
    bsp.splitRecursive(NULL, 8, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f, 1.5f);
    BspListener listener(*this);
    bsp.traverseInvertedLevelOrder(&listener, NULL);
}

//Деконструкторы
Map::~Map()
{
	delete[] tiles;
    delete[] map;
}

//Функции
bool Map::is_wall(int x, int y) const
{
    return !map->isWalkable(x, y);
}

bool Map::can_walk(int x, int y) const
{
    if (is_wall(x, y)) return false;
    for (Character** iterator = game.characters.begin(); iterator != game.characters.end(); iterator++)
    {
        Character* character = *iterator;
        if (character->blocks && character->x == x && character->y == y)
        {
            return false;
        }
    }
    return true;
}

bool Map::is_explored(int x, int y) const
{
    return tiles[x + y * width].explored;
}

bool Map::is_in_Fov(int x, int y) const
{
    if (map->isInFov(x, y))
    {
        tiles[x + y * width].explored = true;
        return true;
    }
    return false;
}

void Map::create_fov()
{
    map->computeFov(game.player->x, game.player->y, game.fov_radius);
}

void Map::dig(int x1, int y1, int x2, int y2) 
{
    if (x1 > x2) 
    {
        int swap = x2;
        x2 = x1;
        x1 = swap;
    }
    if (y1 > y2) 
    {
        int swap = y2;
        y2 = y1;
        y1 = swap;
    }
    for (int i = x1; i <= x2; i++) 
    {
        for (int j = y1; j <= y2; j++) 
        {
            map->setProperties(i,j,true,true);
        }
    }
}

void Map::create_room(bool first, int x1, int y1, int x2, int y2) 
{
    dig(x1, y1, x2, y2);
    if (first) 
    {
        // put the player in the first room
        game.player->x = (x1 + x2) / 2;
        game.player->y = (y1 + y2) / 2;
    }
    else 
    {
        TCODRandom* rng = TCODRandom::getInstance();
        int nb_monsters = rng->getInt(1, max_monsters);
        while (nb_monsters > 0)
        {
            int x = rng->getInt(x1, x2);
            int y = rng->getInt(y1, y2);
            if (can_walk(x, y)) 
            {
                add_monster(x, y);
            }
            nb_monsters--;
        }
    }
}

void Map::add_monster(int x, int y) 
{
    setlocale(LC_ALL, "Russian");
    TCODRandom* rng = TCODRandom::getInstance();
    if (rng->getInt(0, 100) < 80) 
    {
        Character* enemy1 = new Character(x, y, '#', "Первокурсник", TCODColor::fuchsia);
        enemy1->target = new Enemy_Target(10, 2);
        enemy1->attacker = new Attacker(5);
        enemy1->ai = new Enemy_ai();
        //первый враг - 80% появления
        game.characters.push(new Character(x, y, '#', "Первокурсник", TCODColor::fuchsia));
    }
    else 
    {
        Character* enemy2 = new Character(x, y, '*', "Второкурсник", TCODColor::darkFuchsia);
        enemy2->target = new Enemy_Target(20, 5);
        enemy2->attacker = new Attacker(7);
        enemy2->ai = new Enemy_ai();
        //второй враг - 20 % появления
        game.characters.push(new Character(x, y, '*', "Второкурсник", TCODColor::darkFuchsia));
    }
}

void Map::render() const
{
    static const TCODColor lightWall(0, 0, 100);
    static const TCODColor lightGround(50, 50, 150);
	static const TCODColor dark_wall(150, 50, 50);
	static const TCODColor dark_ground(225, 75, 75);
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
            if (is_in_Fov(x, y)) {
                TCODConsole::root->setCharBackground(x, y,
                    is_wall(x, y) ? lightWall : lightGround);
            }
            else if (is_explored(x, y)) {
                TCODConsole::root->setCharBackground(x, y,
                    is_wall(x, y) ? dark_wall : dark_ground);
            }
		}
	}
}