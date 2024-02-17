#ifndef RECHARGE_H
#define RECHARGE_H

#include "Spell.h"

class Recharge : public Spell
{
public:
    Recharge() : Spell(229) {};
    void apply(Boss& boss, Player& player) override;
    void finishTurn(Boss& boss, Player& player) override;
};

#endif