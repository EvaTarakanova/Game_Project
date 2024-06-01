#ifndef MAP_HPP
#define MAP_HPP

#include "libtcod.hpp"

static const int max_monsters = 3;

struct Tile
{
	bool explored;
	Tile() : explored(false) {};
};

static const int ROOM_MAX_SIZE = 12;
static const int ROOM_MIN_SIZE = 6;

class Map
{
public:
	int width, height;

	Map(int widht, int height);
	~Map();

	//Функции
	bool is_in_Fov(int x, int y) const;
	bool is_explored(int x, int y) const;
	bool is_wall(int x, int y) const;
	void create_fov();
	bool can_walk(int x, int y) const;
	void render() const;

protected:
	Tile* tiles;
	TCODMap* map;
	friend class BspListener;

	//Функции
	void dig(int x1, int y1, int x2, int y2);
	void create_room(bool first, int x1, int y1, int x2, int y2);
	void add_monster(int x, int y);
};

#endif //MAP_HPP