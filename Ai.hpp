#ifndef AI_HPP
#define AI_HPP

class Character;

class Ai
{
public:
	virtual void update(Character* owner) = 0;
};

class Player_ai : public Ai
{
public:
	void update(Character *owner);
protected:
	bool move_attack(Character* owner, int target_x, int target_y);
};

class Enemy_ai : public Ai
{
public:
	void update(Character* owner);
protected:
	void move_attack(Character* owner, int target_x, int target_y);
};

#endif // !AI_HPP