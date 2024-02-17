#include "Recharge.h"

void Recharge::apply(Boss& boss, Player& player)
{
    if(this->remainingTurns == 0)
    {
        player.mana -= mana;
        this->remainingTurns = 5;
    }
}

void Recharge::finishTurn(Boss& boss, Player& player)
{
    if(this->remainingTurns > 0)
    {
        player.mana += 101;
        this->remainingTurns--;
    }
}