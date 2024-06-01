#ifndef GAME_HPP
#define GAME_HPP

#include <libtcod.hpp>

class Character;
class Map;

class Game
{
public:
	TCODList<Character*> characters;
	Character* player;
	Map* map;
	int fov_radius;
	int screen_width;
	int screen_height;
	TCOD_key_t last_key;

	enum status
	{
		START,
		EMPTY,
		NEW_TURN,
		VICTORY,
		DEFEAT
	} game_status;

	Game(int screen_width, int screen_height);
	~Game();
	bool create_fov;
	void go_background(Character* character);
	void update();
	void render();
};

extern Game game;

#endif //GAME_HPP