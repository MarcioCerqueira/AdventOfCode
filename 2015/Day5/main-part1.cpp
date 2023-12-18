#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <ranges>

int main(int argc, char **argv)
{
    const std::unordered_set<char> vowels{'a', 'e', 'i', 'o', 'u'};
    const std::unordered_set<std::string> bannedStrings{"ab", "cd", "pq", "xy"};
    const auto isVowel = [vowels](const char character){ return vowels.find(character) != vowels.end(); };
    const auto isBannedString = [bannedStrings](const char a, const char b){ return bannedStrings.find(std::string(1, a) + std::string(1, b)) != bannedStrings.end(); };
    const auto areAdjacentLettersEqual = [](const char a, const char b){ return a == b; };
    
    std::string input;
    int niceStrings{0};
    while(std::cin >> input)
    {
        const int numberOfVowels = std::ranges::count_if(input, isVowel);
        const auto hasBannedString = std::ranges::adjacent_find(input, isBannedString);
        const auto hasDoubleLetter = std::ranges::adjacent_find(input, areAdjacentLettersEqual);
        if(numberOfVowels > 2 && hasBannedString == input.end() && hasDoubleLetter != input.end()) niceStrings++;
    }

    std::cout << "Nice strings: " << niceStrings << std::endl;
}