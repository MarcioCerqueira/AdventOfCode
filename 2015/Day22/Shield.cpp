#include "Shield.h"

void Shield::apply(Boss& boss, Player& player)
{
    if(this->remainingTurns == 0)
    {
        player.armor += 7;
        player.mana -= mana;
        this->remainingTurns = 6;
    }
}

void Shield::finishTurn(Boss& boss, Player& player)
{
    if(this->remainingTurns > 0) 
    {
        this->remainingTurns--;
        if(this->remainingTurns == 0)
        {
            player.armor -= 7;
        }
    }
}