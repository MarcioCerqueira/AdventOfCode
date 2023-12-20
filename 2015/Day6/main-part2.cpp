#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <ranges>
#include <algorithm>

struct Position
{
    int x;
    int y;

    Position(const std::string& coordinate)
    {
        std::stringstream stringStream(coordinate);
        std::string xCoordinate, yCoordinate;
        std::getline(stringStream, xCoordinate, ',');
        std::getline(stringStream, yCoordinate, ',');
        x = std::atoi(xCoordinate.c_str());
        y = std::atoi(yCoordinate.c_str());
    }
};

int main(int argc, char **argv)
{
    std::vector<int> grid;
    grid.resize(1000 * 1000);

    std::string instruction;
    while(std::getline(std::cin, instruction))
    { 
        std::stringstream stringStream(instruction);
        std::string turnOrToggle, onOrOff, sourceCoordinates, through, targetCoordinates;
        std::getline(stringStream, turnOrToggle, ' ');
        if(turnOrToggle == "turn") std::getline(stringStream, onOrOff, ' ');
        std::getline(stringStream, sourceCoordinates, ' ');
        std::getline(stringStream, through, ' ');
        std::getline(stringStream, targetCoordinates, ' ');
        
        const Position source(sourceCoordinates), target(targetCoordinates);
        for(int x = source.x; x <= target.x; x++) {
            for(int y = source.y; y <= target.y; y++) {
                if(turnOrToggle == "turn" && onOrOff == "on") grid[y * 1000 + x]++;
                else if(turnOrToggle == "turn" && onOrOff == "off") grid[y * 1000 + x]--;
                else grid[y * 1000 + x] += 2;
                grid[y * 1000 + x] = std::max<int>(grid[y * 1000 + x], 0);
            }
        } 
    }

    std::cout << "Total brightness: " << std::ranges::fold_left(grid, 0, std::plus<int>()) << std::endl;
}