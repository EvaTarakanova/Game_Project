#include "main.hpp"

void Player_ai::update(Character* owner)
{
	if (owner->target && owner->target->is_dead()) return;
    int dx = 0; int dy = 0;
    switch (game.last_key.vk) 
    {
    case TCODK_UP: dy = -1; break;
    case TCODK_DOWN: dy = 1; break;
    case TCODK_LEFT: dx = -1; break;
    case TCODK_RIGHT: dx = 1; break;
    default:break;
    }
    if (dx != 0 || dy != 0)
    {
        game.game_status = Game:: NEW_TURN;
        if (move_attack(owner, owner->x + dx, owner->y + dy))
        {
            game.map->create_fov();
        }
    }
}

bool Player_ai::move_attack(Character *owner, int target_x, int target_y)
{
    if (game.map->is_wall(target_x, target_y)) return false;
    for (Character** iterator = game.characters.begin(); iterator != game.characters.end(); iterator++)
    {
        Character* character = *iterator;
        if (character->target && !character->target->is_dead() && character->x == target_x && character->y == target_y)
        {
            owner->attacker->attack(owner, character);
            return false;
        }
    }
    owner->x = target_x;
    owner->y = target_y;
    return true;
}

void Enemy_ai::update(Character* owner)
{
    if (owner->target && owner->target->is_dead()) return;
    if (game.map->is_in_Fov(owner->x, owner->y))
    {
        move_attack(owner, game.player->x, game.player->y);
    }
}

void Enemy_ai::move_attack(Character* owner, int target_x, int target_y)
{
    int dx = target_x - owner->x;
    int dy = target_y - owner->y;
    float distance = sqrt(dx * dx + dy * dy);
    if (distance >= 2)
    {
        dx = (int)(round(dx / distance));
        dy = (int)(round(dy / distance));
    }
    if (game.map->can_walk(owner->x + dx, owner->y + dy))
    {
        owner->x += dx;
        owner->y += dy;
    }
    else if (owner->attacker)
    {
        owner->attacker->attack(owner, game.player);
    }
}