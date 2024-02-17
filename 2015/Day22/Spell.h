#ifndef SPELL_H
#define SPELL_H

#include "Boss.h"
#include "Player.h"

struct Boss;
struct Player;

class Spell
{
public:
    Spell(unsigned int mana) : mana(mana), remainingTurns(0) {};
    virtual void apply(Boss& boss, Player& player) = 0;
    virtual void finishTurn(Boss& boss, Player& player) = 0; 
    unsigned int getMana() const { return mana; };
    bool isActive() const { return remainingTurns > 0; };
    bool isCastable(unsigned int playerMana) const { return playerMana > mana; };
protected:
    int remainingTurns;
    unsigned int mana;
};

#endif