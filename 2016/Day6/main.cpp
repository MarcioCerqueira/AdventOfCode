#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <ranges>

int main(int argc, char **argv)
{
    std::vector<std::string> messages;
    std::string message;
    while(std::cin >> message) messages.push_back(message);

    std::vector<std::unordered_map<char, int>> charToOccurrenceMap;
    charToOccurrenceMap.resize(message.size());
    std::ranges::for_each(messages, [&](const std::string& message){
        std::ranges::for_each(std::views::iota(0, static_cast<int>(message.size())), [&](const int index){
            charToOccurrenceMap[index][message[index]]++;
        });
    });

    std::string errorCorrectedMessage;
    std::ranges::for_each(charToOccurrenceMap, [&](const std::unordered_map<char, int> charToOccurrencePerPositionMap){
        const auto pairWithMaxOccurrence = std::ranges::max_element(charToOccurrencePerPositionMap, [&](const std::pair<char,int>& a, const std::pair<char,int>& b){
            return a.second < b.second;
        });
        errorCorrectedMessage += pairWithMaxOccurrence->first;
    });

    std::string originalMessage;
    std::ranges::for_each(charToOccurrenceMap, [&](const std::unordered_map<char, int> charToOccurrencePerPositionMap){
        const auto pairWithMaxOccurrence = std::ranges::max_element(charToOccurrencePerPositionMap, [&](const std::pair<char,int>& a, const std::pair<char,int>& b){
            return a.second > b.second;
        });
        originalMessage += pairWithMaxOccurrence->first;
    });

    std::cout << "Error Corrected Message: " << errorCorrectedMessage << std::endl;
    std::cout << "Original Message: " << originalMessage << std::endl;
}