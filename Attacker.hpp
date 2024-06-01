#ifndef ATTACKER_HPP
#define ATTACKER_HPP

class Character;

class Attacker
{
public:
	float power;

	Attacker(float power);
	void attack(Character* owner, Character* enemy);
};

#endif // !ATTACKER_HPP