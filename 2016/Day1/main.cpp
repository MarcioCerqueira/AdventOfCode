#include <iostream>
#include <string>
#include <ranges>
#include <algorithm>
#include <unordered_set>
#include <memory>

struct Position
{
    int x{0};
    int y{0};
    std::string getID()
    {
        return std::to_string(x) + "," + std::to_string(y);
    }
};

struct Direction
{
    int x{0};
    int y{1};
};

struct Character
{
    Position position;
    Direction direction;
};

int main(int argc, char **argv)
{
    std::string path;
    std::getline(std::cin, path);
    
    Character character;
    std::optional<Position> easterBunnyHQ;
    std::unordered_set<std::string> visitedLocations;
    const auto walk = [&character, &easterBunnyHQ, &visitedLocations](const auto instruction){
        const auto instructionView{std::string_view(instruction)};
        if(instructionView.starts_with('R')) {
            character.direction.x *= -1;
            std::swap(character.direction.x, character.direction.y);
        } else {
            character.direction.y *= -1;    
            std::swap(character.direction.x, character.direction.y);
        }

        const int distance{atoi(instructionView.substr(1).data())};
        std::ranges::for_each(std::views::iota(1, distance + 1), [&character, &easterBunnyHQ, &visitedLocations](const int index){
            character.position.x += character.direction.x;
            character.position.y += character.direction.y;
            if(visitedLocations.contains(character.position.getID()) && !easterBunnyHQ.has_value()) easterBunnyHQ = character.position;
            visitedLocations.insert(character.position.getID());
        });
    };

    std::ranges::for_each(std::views::split(std::string_view(path), std::string_view(", ")), walk);
    std::cout << "(Part I) Shortest path to Easter Bunny HQ is: " << abs(character.position.x) + abs(character.position.y) << " blocks away" << std::endl;
    std::cout << "(Part II) Shortest path to Easter Bunny HQ is: " << abs(character.position.x - easterBunnyHQ.value_or(Position()).x) + abs(character.position.y - easterBunnyHQ.value_or(Position()).y) << " blocks away" << std::endl;
}