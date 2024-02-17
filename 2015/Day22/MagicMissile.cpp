#include "MagicMissile.h"

void MagicMissile::apply(Boss& boss, Player& player)
{
    boss.hitPoints -= 4;
    player.mana -= mana;
    this->remainingTurns = 0;
}

void MagicMissile::finishTurn(Boss& boss, Player& player)
{
    this->remainingTurns = 0;
}