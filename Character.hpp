#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "libtcod.hpp"
#include "Target.hpp"
#include "Attacker.hpp"
#include "Ai.hpp"

class Attacker;
class Target;
class Ai;

class Character
{
public:
	int x, y;
	int sym; //Переменной sym будет принадлежать ascii cod, поэтому он инт
	TCODColor color;
	const char *name;
	bool blocks;
	Attacker *attacker;
	Target *target;
	Ai *ai;


	Character(int x, int y, int sym, const char* name, const TCODColor& color);
	void render() const;
	void update();
};

#endif //CHARACTER_HPP