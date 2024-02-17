#ifndef DRAIN_H
#define DRAIN_H

#include "Spell.h"

class Drain : public Spell
{
public:
    Drain() : Spell(73) {};
    void apply(Boss& boss, Player& player) override;
    void finishTurn(Boss& boss, Player& player) override;
};

#endif