#include <iostream>
#include <string>
#include <ranges>
#include <unordered_map>
#include <algorithm>

void increment(std::string& input)
{
    for(int index = input.size() - 1; index >= 0; index--)
    {
        if(input[index] != 'z') 
        {
            input[index]++;
            return;
        }
        input[index] = 'a';
    } 
}

bool checkThirdRule(const std::string& password)
{
    const auto hasAdjacentPair = [](const std::tuple<char, char>& pair) { return std::get<0>(pair) == std::get<1>(pair); };
    const auto hasDuplicatedPair = [](const std::pair<char, int>& pair) { return pair.second == 2; };
    auto thirdRule = password | std::views::adjacent<2> | std::views::filter(hasAdjacentPair);
    
    std::unordered_map<char, int> charCount;
    std::ranges::for_each(thirdRule, [&charCount](const auto pair){ charCount[pair.first] += 2; });
    
    return charCount.size() >= 2 && std::ranges::all_of(charCount, hasDuplicatedPair);
}

int main(int argc, char **argv)
{
    std::string password;
    std::cin >> password;

    const auto hasStraightOfThreeLetters = [](const std::tuple<char, char, char>& string) { return std::get<0>(string) == std::get<1>(string) - 1 && std::get<1>(string) == std::get<2>(string) - 1; };
    const auto hasBannedLetter = [](const char letter) { return letter == 'i' || letter == 'o' || letter == 'l'; };

    while(true)
    {
        increment(password);
        auto straightOfThreeLetters = password | std::views::adjacent<3> | std::views::filter(hasStraightOfThreeLetters);
        auto bannerLetter = std::ranges::find_if(password, hasBannedLetter);
        auto hasDifferentNonOverlappingPairs = checkThirdRule(password);
        if(straightOfThreeLetters.empty() || bannerLetter != password.end() || !hasDifferentNonOverlappingPairs) continue;
        break;
    }

    std::cout << "Next valid password: " << password << std::endl;
    return 0;
}