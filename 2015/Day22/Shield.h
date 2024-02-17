#ifndef SHIELD_H
#define SHIELD_H

#include "Spell.h"

class Shield : public Spell
{
public:
    Shield() : Spell(113) {};
    void apply(Boss& boss, Player& player) override;
    void finishTurn(Boss& boss, Player& player) override;
};

#endif