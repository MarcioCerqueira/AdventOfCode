#include <iostream>
#include <string>
#include <ranges>
#include <algorithm>

std::string lookAndSay(const std::string& sequence)
{
    int count{0};
    char previousCharacter = sequence[0];
    std::string output;

    std::ranges::for_each(sequence, [&](const char character){
        if(character == previousCharacter) 
        {
            count++;
        }
        else
        {
            output += std::to_string(count);
            output += previousCharacter;
            count = 1;
        }
        previousCharacter = character;
    });

    if(count > 0)
    {
        output += std::to_string(count);
        output += previousCharacter;
    }

    return output;
}

int main(int argc, char **argv)
{
    std::string sequence;
    std::cin >> sequence;

    std::ranges::for_each(std::views::iota(0, 50), [&sequence](int i){ sequence = lookAndSay(sequence); });
    std::cout << "Length of the result after 50 iterations: " << sequence.length() << std::endl;
    return 0;
}