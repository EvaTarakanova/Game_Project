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

	enum status
	{
		START,
		EMPTY,
		NEW_TURN,
		VICTORY,
		DEFEAT
	} game_status;

	Game();
	~Game();
	bool create_fov;
	void update();
	void render();
};

extern Game game;

#endif //GAME_HPP