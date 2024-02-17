#ifndef BOSS_H
#define BOSS_H

#include "Player.h"

struct Player;

struct Boss
{
    int hitPoints{71};
    int damage{10};

    bool isAlive() const;
    void fight(Player& player);
};

#endif