#include "Poison.h"

void Poison::apply(Boss& boss, Player& player)
{
    if(this->remainingTurns == 0)
    {
        player.mana -= mana;
        this->remainingTurns = 6;
    }
}

void Poison::finishTurn(Boss& boss, Player& player)
{
    if(this->remainingTurns > 0)
    {
        boss.hitPoints -= 3;
        this->remainingTurns--;
    }
}