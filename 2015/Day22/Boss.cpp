#include "Boss.h"
#include <iostream>
bool Boss::isAlive() const
{
    return hitPoints > 0;
}

void Boss::fight(Player& player)
{
    player.hitPoints -= std::max(damage - player.armor, 1);
}