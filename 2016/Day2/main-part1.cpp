#include <iostream>
#include <array>
#include <string>
#include <algorithm>

struct Position
{
    int x{1};
    int y{1};
};

void loadKeyPad(std::array<std::array<char, 3>, 3>& keyPad)
{
    keyPad[0][0] = '1';
    keyPad[0][1] = '2';
    keyPad[0][2] = '3';
    keyPad[1][0] = '4';
    keyPad[1][1] = '5';
    keyPad[1][2] = '6';
    keyPad[2][0] = '7';
    keyPad[2][1] = '8';
    keyPad[2][2] = '9';
}

int main(int argc, char **argv)
{
    std::array<std::array<char, 3>, 3> keyPad;
    loadKeyPad(keyPad);

    std::string instruction;
    std::string bathroomCode;
    Position position;
    while(std::getline(std::cin, instruction))
    {
        std::ranges::for_each(instruction, [&position](const char direction){
            if(direction == 'U') position.y = std::max(position.y - 1, 0);
            else if(direction == 'L') position.x = std::max(position.x - 1, 0);
            else if(direction == 'R') position.x = std::min(position.x + 1, 2);
            else if(direction == 'D') position.y = std::min(position.y + 1, 2);
        });
        bathroomCode = bathroomCode + keyPad[position.y][position.x];
    }

    std::cout << "Bathroom code: " << bathroomCode << std::endl;
}