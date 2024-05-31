#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "libtcod.hpp"

class Character
{
public:
	int x, y;
	int sym; //Переменной sym будет принадлежать ascii cod, поэтому он инт
	TCODColor color;
	const char *name;
	bool blocks;
	//Attacker* attacker;
	//Target* target;
	//Ai* ai;


	Character(int x, int y, int sym, const char* name, const TCODColor& color);
	void render() const;
	void update();
	bool move_attack(int x, int y);
};

#endif //CHARACTER_HPP