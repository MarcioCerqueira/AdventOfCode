#ifndef MAGIC_MISSILE_H
#define MAGIC_MISSILE_H

#include "Spell.h"

class MagicMissile : public Spell
{
public:
    MagicMissile() : Spell(53) {};
    void apply(Boss& boss, Player& player) override;
    void finishTurn(Boss& boss, Player& player) override;
};

#endif