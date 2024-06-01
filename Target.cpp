#include <stdio.h>
#include "main.hpp"

Target::Target(float max_hp, float defense) : max_hp(max_hp), current_hp(current_hp), defense(defense){}

float Target::take_damage(Character *owner, float damage)
{
	damage -= defense;
	if (damage > 0)
	{
		current_hp -= damage;
		if (current_hp < 0)
		{
			die(owner);
		}
	}
	else
	{
		damage = 0;
	}
	return damage;
}

void Target::die(Character *owner)
{
	owner->sym = 'X';
	owner->color = TCODColor::desaturatedRed;
	owner->blocks = false;
	game.go_background(owner);
}

Enemy_Target::Enemy_Target(float max_hp, float defense) : Target(max_hp,defense){}

void Enemy_Target::die(Character* owner)
{
	printf("%n получил незачёт", owner->name);
	Target::die(owner);
}

Player_Target::Player_Target(float max_hp, float defense) : Target(max_hp, defense) {}

void Player_Target::die(Character* owner)
{
	printf("Студенты победили", owner->name);
	Target::die(owner);
	game.game_status = Game::DEFEAT;
}

