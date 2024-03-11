#include <iostream>
#include <array>
#include <string>
#include <algorithm>

struct Position
{
    int x{0};
    int y{2};
};

void loadKeyPad(std::array<std::array<char, 5>, 5>& keyPad)
{
    keyPad[0][0] = ' ';
    keyPad[0][1] = ' ';
    keyPad[0][2] = '1';
    keyPad[0][3] = ' ';
    keyPad[0][4] = ' ';
    keyPad[1][0] = ' ';
    keyPad[1][1] = '2';
    keyPad[1][2] = '3';
    keyPad[1][3] = '4';
    keyPad[1][4] = ' ';
    keyPad[2][0] = '5';
    keyPad[2][1] = '6';
    keyPad[2][2] = '7';
    keyPad[2][3] = '8';
    keyPad[2][4] = '9';
    keyPad[3][0] = ' ';
    keyPad[3][1] = 'A';
    keyPad[3][2] = 'B';
    keyPad[3][3] = 'C';
    keyPad[3][4] = ' ';
    keyPad[4][0] = ' ';
    keyPad[4][1] = ' ';
    keyPad[4][2] = 'D';
    keyPad[4][3] = ' ';
    keyPad[4][4] = ' ';
}

int main(int argc, char **argv)
{
    std::array<std::array<char, 5>, 5> keyPad;
    loadKeyPad(keyPad);

    std::string instruction;
    std::string bathroomCode;
    Position position;
    while(std::getline(std::cin, instruction))
    {
        std::ranges::for_each(instruction, [&position, keyPad](const char direction){
            if(direction == 'U') position.y = std::max(position.y - 1, 0);
            else if(direction == 'L') position.x = std::max(position.x - 1, 0);
            else if(direction == 'R') position.x = std::min(position.x + 1, 4);
            else if(direction == 'D') position.y = std::min(position.y + 1, 4);

            if(keyPad[position.y][position.x] == ' ') {
                if(direction == 'U') ++position.y;
                else if(direction == 'L') ++position.x;
                else if(direction == 'R') --position.x;
                else if(direction == 'D') --position.y;
            }
        });
        bathroomCode = bathroomCode + keyPad[position.y][position.x];
    }

    std::cout << "Bathroom code: " << bathroomCode << std::endl;
}