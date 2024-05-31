#include "Character.hpp"
#include "main.hpp"

Character::Character(int x, int y, int sym, const char* name, const TCODColor& color) : x(x), y(y), sym(sym), name(name), color(color), blocks(true) {}//, attacker(NULL), target(NULL), ai(NULL) {}

void Character::render() const
{
    TCODConsole::root->setChar(x, y, sym); //��������� ascii ����
    TCODConsole::root->setCharForeground(x, y, color); //��������� ����� ��� ascii ������
}

void Character::update()
{
    //if (ai) ai->update(this);
    setlocale(LC_ALL, "Russian");
    printf("%s ��� ����, �� ������ �������� ����� \n", name);
}

bool Character::move_attack(int x, int y)
{
    if (game.map->is_wall(x, y)) return false;
    for (Character** iterator = game.characters.begin(); iterator != game.characters.end(); iterator++) 
    {
        Character* character = *iterator;
        if (character->x == x && character->y == y) 
        {
            printf("The %s laughs at your puny efforts to attack him!\n",
                character->name);
            return false;
        }
    }
    this->x = x;
    this->y = y;
    return true;
}