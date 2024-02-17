#include "Player.h"

bool Player::isAlive() const 
{
    return hitPoints > 0 && mana > 0;
}

void Player::fight(Boss &boss, const std::unique_ptr<Spell>& spell)
{
    spell->apply(boss, *this);
}