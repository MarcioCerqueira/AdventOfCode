#include <iostream>
#include <optional>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <ranges>

struct Weapon
{
    std::string name;
    int cost{0};
    int damage{0};
};

struct Armor
{
    std::string name;
    int cost{0};
    int armor{0};
};

struct Ring
{
    std::string name;
    int cost{0};
    int damage{0};
    int armor{0};
};

struct Player
{
    int moneySpent{0};
    int hitPoints{100};
    Weapon weapon;
    std::optional<Armor> armor;
    std::array<std::optional<Ring>, 2> rings;
};

struct Boss
{
    int hitPoints{100};
    int damage{0};
    int armor{0};
};

std::vector<Weapon> loadWeapons()
{
    std::vector<Weapon> weapons;
    weapons.push_back(Weapon{.name = "Dagger", .cost = 8, .damage = 4});
    weapons.push_back(Weapon{.name = "Shortsword", .cost = 10, .damage = 5});
    weapons.push_back(Weapon{.name = "Warhammer", .cost = 25, .damage = 6});
    weapons.push_back(Weapon{.name = "Longsword", .cost = 40, .damage = 7});
    weapons.push_back(Weapon{.name = "Greataxe", .cost = 74, .damage = 8});
    return weapons;
}

std::vector<std::optional<Armor>> loadArmors()
{
    std::vector<std::optional<Armor>> armors;
    armors.push_back(std::nullopt);
    armors.push_back(Armor{.name = "Leather", .cost = 13, .armor = 1});
    armors.push_back(Armor{.name = "Chainmail", .cost = 31, .armor = 2});
    armors.push_back(Armor{.name = "Splintmail", .cost = 53, .armor = 3});
    armors.push_back(Armor{.name = "Bandedmail", .cost = 75, .armor = 4});
    armors.push_back(Armor{.name = "Platemail", .cost = 102, .armor = 5});
    return armors;
}

std::vector<std::optional<Ring>> loadRings()
{
    std::vector<std::optional<Ring>> rings;
    rings.push_back(std::nullopt);
    rings.push_back(Ring{.name = "Damage +1", .cost = 25, .damage = 1, .armor = 0});
    rings.push_back(Ring{.name = "Damage +2", .cost = 50, .damage = 2, .armor = 0});
    rings.push_back(Ring{.name = "Damage +3", .cost = 100, .damage = 3, .armor = 0});
    rings.push_back(Ring{.name = "Defense +1", .cost = 20, .damage = 0, .armor = 1});
    rings.push_back(Ring{.name = "Defense +2", .cost = 40, .damage = 0, .armor = 2});
    rings.push_back(Ring{.name = "Defense +3", .cost = 80, .damage = 0, .armor = 3});
    return rings;
}

Boss loadBoss()
{
    return Boss{
        .hitPoints = 103,
        .damage = 9,
        .armor = 2
    };
}

bool fightBoss(Player player, Boss boss)
{
    const int totalPlayerDamage{player.weapon.damage + player.rings[0].value_or(Ring{}).damage + player.rings[1].value_or(Ring{}).damage};
    const int totalPlayerArmor{player.armor.value_or(Armor{}).armor + player.rings[0].value_or(Ring{}).armor + player.rings[1].value_or(Ring{}).armor};
    
    while(true)
    {
        boss.hitPoints -= std::max(totalPlayerDamage - boss.armor, 1);
        if(boss.hitPoints <= 0) return true;

        player.hitPoints -= std::max(boss.damage - totalPlayerArmor, 1);
        if(player.hitPoints <= 0) return false;
    }
}

int main(int argc, char **argv)
{
    const std::vector<Weapon> weapons{loadWeapons()};
    const std::vector<std::optional<Armor>> armors(loadArmors());
    const std::vector<std::optional<Ring>> rings(loadRings());
    Boss boss(loadBoss());
    Player player; 

    const auto byValidRings = [](const std::tuple<Weapon, std::optional<Armor>, std::optional<Ring>, std::optional<Ring>>& item){
        const auto& [weapon, armor, firstRing, secondRing] = item;
        return !firstRing.has_value() || !secondRing.has_value() || firstRing.value_or(Ring{}).name != secondRing.value_or(Ring{}).name;
    };

    const auto byWins = [=](const std::tuple<Weapon, std::optional<Armor>, std::optional<Ring>, std::optional<Ring>>& item) mutable {
        const auto& [weapon, armor, firstRing, secondRing] = item;
        player.weapon = weapon;
        player.armor = armor;
        player.rings[0] = firstRing;
        player.rings[1] = secondRing;
        return fightBoss(player, boss);
    };

    const auto toCost = [](const std::tuple<Weapon, std::optional<Armor>, std::optional<Ring>, std::optional<Ring>>& item) {
        const auto& [weapon, armor, firstRing, secondRing] = item;
        return weapon.cost + armor.value_or(Armor{}).cost + firstRing.value_or(Ring{}).cost + secondRing.value_or(Ring{}).cost;
    };

    auto bestCosts = std::views::cartesian_product(weapons, armors, rings, rings) 
        | std::views::filter(byValidRings) | std::views::filter(byWins) | std::views::transform(toCost);
    
    std::cout << "Least amount of gold needed to win a fight: " << std::ranges::min(bestCosts) << std::endl;

    const auto byLoses = [=](const std::tuple<Weapon, std::optional<Armor>, std::optional<Ring>, std::optional<Ring>>& item) mutable {
        const auto& [weapon, armor, firstRing, secondRing] = item;
        player.weapon = weapon;
        player.armor = armor;
        player.rings[0] = firstRing;
        player.rings[1] = secondRing;
        return !fightBoss(player, boss);
    };

    auto worstCosts = std::views::cartesian_product(weapons, armors, rings, rings) 
        | std::views::filter(byValidRings) | std::views::filter(byLoses) | std::views::transform(toCost);
    
    std::cout << "Highest amount of gold needed to lose a fight: " << std::ranges::max(worstCosts) << std::endl;

}