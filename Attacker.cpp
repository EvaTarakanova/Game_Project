#include <stdio.h>
#include "main.hpp"

Attacker::Attacker(float power) : power(power){}

void Attacker::attack(Character *owner, Character *enemy)
{
	if (enemy->target && !enemy->target->is_dead())
	{
		if (power - enemy->target->defense > 0)
		{
			std::cout << "%s attacks %s for %g hit points.\n";
		}
		else
		{
			std:: cout << "Not enough sternght";
		}
		enemy->target->take_damage(enemy, power);
	};
}