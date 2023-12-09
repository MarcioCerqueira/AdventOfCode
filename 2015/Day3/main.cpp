#include <iostream>
#include <unordered_set>
#include <string>

struct Position
{
    int x;
    int y;

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
};

int main(int argc, char **argv)
{
    std::string directions;
    std::cin >> directions;
    
    std::unordered_set<std::string> houseIds;
    Position santaPosition(0, 0), robotSantaPosition(0, 0), movement(0, 0);

    houseIds.insert(santaPosition.toID());
    bool santaMoves = true;
    for(char direction : directions)
    {
        if(direction == '<') movement = Position(-1, 0);
        else if(direction == '^') movement = Position(0, 1);
        else if(direction == '>') movement = Position(1, 0);
        else movement = Position(0, -1);
        
        if(santaMoves) 
        {
            santaPosition += movement;
            houseIds.insert(santaPosition.toID());
        }
        else
        {
            robotSantaPosition += movement;
            houseIds.insert(robotSantaPosition.toID());
        }
        santaMoves = !santaMoves;
    }

    std::cout << "Visited Houses: " << houseIds.size() << std::endl;
    return 0;
}

