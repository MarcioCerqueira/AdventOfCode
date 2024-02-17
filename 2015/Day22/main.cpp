#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <memory>
#include <algorithm>
#include <ranges>

#include "Player.h"
#include "Boss.h"
#include "Spell.h"
#include "MagicMissile.h"
#include "Drain.h"
#include "Shield.h"
#include "Poison.h"
#include "Recharge.h"

std::array<std::unique_ptr<Spell>, 5> loadSpells()
{
    return std::array<std::unique_ptr<Spell>, 5> { std::make_unique<MagicMissile>(), 
        std::make_unique<Drain>(), 
        std::make_unique<Shield>(), 
        std::make_unique<Poison>(), 
        std::make_unique<Recharge>() 
    };
}

std::array<std::unique_ptr<Spell>, 5> copySpells(std::array<std::unique_ptr<Spell>, 5>& spells)
{
    return std::array<std::unique_ptr<Spell>, 5> { std::make_unique<MagicMissile>(dynamic_cast<MagicMissile&>(*spells[0])), 
        std::make_unique<Drain>(dynamic_cast<Drain&>(*spells[1])), 
        std::make_unique<Shield>(dynamic_cast<Shield&>(*spells[2])), 
        std::make_unique<Poison>(dynamic_cast<Poison&>(*spells[3])), 
        std::make_unique<Recharge>(dynamic_cast<Recharge&>(*spells[4])) 
    };
}

unsigned int newRound(Player player, Boss boss, std::array<std::unique_ptr<Spell>, 5>& spells, unsigned int usedMana)
{
    const auto finishTurn = [&](std::unique_ptr<Spell>& spell){ spell->finishTurn(boss, player); };
    const auto cannotBeCasted = [&](const auto& spell){ return !spell->isCastable(player.mana); };
    
    if(!boss.isAlive()) return usedMana;
    if(!player.isAlive()) return UINT_MAX;
    if(std::ranges::all_of(spells, cannotBeCasted)) return UINT_MAX;
    
    std::ranges::for_each(spells, finishTurn);

    if(!boss.isAlive()) return usedMana;
    if(!player.isAlive()) return UINT_MAX;
    if(std::ranges::all_of(spells, cannotBeCasted)) return UINT_MAX;
    
    if(usedMana > 0) boss.fight(player);
    if(!player.isAlive()) return UINT_MAX;

    std::ranges::for_each(spells, finishTurn);
    
    if(!boss.isAlive()) return usedMana;
    if(!player.isAlive()) return UINT_MAX;
    if(std::ranges::all_of(spells, cannotBeCasted)) return UINT_MAX;
    
    //Part two
    if(usedMana > 0) player.hitPoints--;
    if(!player.isAlive()) return UINT_MAX;

    std::vector<unsigned int> totalManaPerRound;
    std::ranges::for_each(std::views::iota(0, static_cast<int>(spells.size())), [&](const int spellIndex){
        Player copiedPlayer{player};
        Boss copiedBoss{boss};
        std::array<std::unique_ptr<Spell>, 5> copiedSpells{copySpells(spells)};

        if(!copiedSpells[spellIndex]->isActive() && copiedSpells[spellIndex]->isCastable(player.mana)) 
        {
            copiedPlayer.fight(copiedBoss, copiedSpells[spellIndex]);
            totalManaPerRound.push_back(newRound(copiedPlayer, copiedBoss, copiedSpells, usedMana + copiedSpells[spellIndex]->getMana()));
        }
    });
    return std::ranges::min(totalManaPerRound);
}

int main(int argc, char **argv)
{
    Player player;
    Boss boss;
    std::array<std::unique_ptr<Spell>, 5> spells{loadSpells()};
    
    std::cout << "Least Amount of Mana: " << newRound(player, boss, spells, 0) << std::endl;
}