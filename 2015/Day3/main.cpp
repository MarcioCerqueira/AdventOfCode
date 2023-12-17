#include <iostream>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <vector>
#include <numeric>
#include <ranges>

struct Position
{
    int x;
    int y;

    Position()
    {
        this->x = 0;
        this->y = 0;
    }

    Position(const int x, const int y)
    {
        this->x = x;
        this->y = y;
    }

    std::string toID()
    {
        return std::to_string(x) + "-" + std::to_string(y);
    }

    void operator+=(const Position& rhs)
    {
        x += rhs.x;
        y += rhs.y;
    }

    Position operator+(const Position& rhs)
    {
        return Position(x + rhs.x, y + rhs.y);
    }
};

int main(int argc, char **argv)
{
    std::string input;
    std::cin >> input;
    
    std::vector<Position> santaPositions, robotSantaPositions;
    std::unordered_set<std::string> houseIds;
    int index;
    
    auto toPosition = [](const char direction) {
        if(direction == '<') return Position(-1, 0);
        if(direction == '^') return Position(0, 1);
        if(direction == '>') return Position(1, 0);
        return Position(0, -1); 
    };

    auto santaMoves = [&index](const Position p){ index++; return index % 2 == 0; };
    auto robotSantaMoves = [&index](const Position p){ index++; return index % 2 == 1; };
    auto insertHouseIds = [&houseIds](Position position){ houseIds.insert(position.toID()); };

    index = -1;
    auto santaDirections = input | std::ranges::views::transform(toPosition) | std::ranges::views::filter(santaMoves);
    std::partial_sum(santaDirections.begin(), santaDirections.end(), std::back_inserter(santaPositions));
    std::ranges::for_each(santaPositions, insertHouseIds);
    
    index = -1;
    auto robotSantaDirections = input | std::ranges::views::transform(toPosition) | std::ranges::views::filter(robotSantaMoves);
    std::partial_sum(robotSantaDirections.begin(), robotSantaDirections.end(), std::back_inserter(robotSantaPositions));
    std::ranges::for_each(robotSantaPositions, insertHouseIds);    
    
    std::cout << "Visited Houses: " << houseIds.size() << std::endl;
    return 0;
}