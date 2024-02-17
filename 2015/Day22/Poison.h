#ifndef POISON_H
#define POISON_H

#include "Spell.h"

class Poison : public Spell
{
public:
    Poison() : Spell(173) {};
    void apply(Boss& boss, Player& player) override;
    void finishTurn(Boss& boss, Player& player) override;
};

#endif