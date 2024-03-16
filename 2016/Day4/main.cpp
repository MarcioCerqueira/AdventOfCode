#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <ranges>

std::vector<std::pair<char, int>> sort(const std::map<char, int>& occurrences)
{
    std::vector<std::pair<char, int>> sortedOccurrences;
    const auto toVector = [](const std::pair<char, int>& pair){ return pair; };
    std::ranges::transform(occurrences, std::back_inserter(sortedOccurrences), toVector);
    const auto comparator = [](const std::pair<char, int>& a, const std::pair<char, int>& b){ 
        if(a.second != b.second) return a.second > b.second;
        return a.first < b.first; 
    };
    std::ranges::sort(sortedOccurrences, comparator);
    return sortedOccurrences;
}

int main(int argc, char** argv)
{
    std::string encryptedName, chosenRoomName;
    int sumOfSectorIDs{0}, chosenSectorID; 
    while(std::cin >> encryptedName)
    {
        const std::string roomName{encryptedName.substr(0, encryptedName.find_first_of('['))};
        const std::string checkSum{encryptedName.substr(encryptedName.find_first_of('[') + 1, 5)};
        const int sectorID{atoi(encryptedName.substr(encryptedName.find_last_of('-') + 1, encryptedName.find_first_of('[')).c_str())};
        
        std::map<char, int> occurrences;
        std::ranges::for_each(roomName, [&](const char character){ if(isalpha(character)) ++occurrences[character]; });
        
        std::vector<std::pair<char, int>> sortedOccurrences{sort(occurrences)};
        const auto isEqual = [](const auto& tuple){ return std::get<0>(tuple) == std::get<1>(tuple).first; };
        const bool isValidRoomName{std::ranges::all_of(std::views::zip(checkSum, sortedOccurrences), isEqual)};
        if(isValidRoomName) sumOfSectorIDs += sectorID;
        
        std::string decryptedRoomName;
        const auto toDecryption = [&sectorID](const char character){ 
            if(character == '-') return ' '; 
            else {
                const int shift{sectorID % 26};
                if(character + shift > 'z') return static_cast<char>((character + shift) - 26);
                return static_cast<char>(character + shift);
            }
        };
        std::ranges::transform(roomName, std::back_inserter(decryptedRoomName), toDecryption);
        if(decryptedRoomName.contains("north")) {
            chosenSectorID = sectorID;
            chosenRoomName = decryptedRoomName;
        }
    }
    std::cout << "Sum of the sector IDs of the real rooms: " << sumOfSectorIDs << std::endl;
    std::cout << chosenSectorID << " is the sector ID of " << chosenRoomName << " where North Pole objects are stored" << std::endl; 
}