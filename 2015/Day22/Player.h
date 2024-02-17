#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

#include "Boss.h"
#include "Spell.h"

struct Boss;
class Spell;

struct Player
{
    int hitPoints{50};
    int mana{500};
    int armor{0};

    bool isAlive() const;
    void fight(Boss &boss, const std::unique_ptr<Spell>& spell);
};

#endif