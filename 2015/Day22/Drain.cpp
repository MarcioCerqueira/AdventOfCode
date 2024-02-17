#include "Drain.h"

void Drain::apply(Boss& boss, Player& player)
{
    boss.hitPoints -= 2;
    player.hitPoints += 2;
    player.mana -= mana;
    this->remainingTurns = 0;
}

void Drain::finishTurn(Boss& boss, Player& player)
{
    this->remainingTurns = 0;
}