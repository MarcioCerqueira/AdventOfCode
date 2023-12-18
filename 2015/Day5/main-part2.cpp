#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <ranges>
#include <tuple>

int main(int argc, char **argv)
{
    std::string input;
    const auto nonOverlappingAdjacentPairs = [&input](const char a, const char b){ 
        const std::string pair = std::string(1, a) + std::string(1, b);
        const size_t firstPair = input.find(pair);
        if (firstPair == std::string::npos) return false;
        const size_t lastPair = input.find(pair, firstPair + 2);
        return (lastPair != std::string::npos); 
    };
    const auto isOneLetterBetweenAPair = [](const std::tuple<char, char, char>& string){ 
        const auto [a, b, c] = string;
        return a == c;
    };
    
    int niceStrings{0};
    while(std::cin >> input)
    {
        const auto hasNonOverlappingAdjacentPairs = std::ranges::adjacent_find(input, nonOverlappingAdjacentPairs);
        auto hasOneLetterBetweenAPair = input | std::views::adjacent<3> | std::views::filter(isOneLetterBetweenAPair);
        if(hasNonOverlappingAdjacentPairs != input.end() && !hasOneLetterBetweenAPair.empty()) niceStrings++;
    }
    std::cout << "Nice strings: " << niceStrings << std::endl;
}