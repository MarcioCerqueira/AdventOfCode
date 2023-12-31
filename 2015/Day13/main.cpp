#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <ranges>
#include <algorithm>
#include <regex>

void loadAffinityMatrix(const std::string& sentence, std::vector<std::vector<int>>& affinityMatrix, std::unordered_map<std::string, int>& personToID)
{
    const std::regex sentenceRegex("(\\w+) would (\\w+) (\\d+) happiness units by sitting next to (\\w+).");
    std::smatch stringMatch;
    std::regex_search(sentence, stringMatch, sentenceRegex);
    
    const std::string sourceName{stringMatch.str(1)};
    const std::string sign{stringMatch.str(2)};
    const int affinity{stoi(stringMatch.str(3))};
    const std::string targetName{stringMatch.str(4)};

    if(!personToID.contains(sourceName)) 
    {
        personToID[sourceName] = affinityMatrix.size();
        affinityMatrix.push_back({0});
    }
    if(!personToID.contains(targetName))
    {
        personToID[targetName] = affinityMatrix.size();
        affinityMatrix.push_back({});
    }

    const int affinityValue = sign == "gain" ? affinity : affinity * -1;
    if(personToID[sourceName] == 0)
    {
        affinityMatrix[personToID[sourceName]].push_back(affinityValue);
    }
    else
    {
        if(affinityMatrix[personToID[sourceName]].size() != personToID.size()) affinityMatrix[personToID[sourceName]].resize(personToID.size());
        affinityMatrix[personToID[sourceName]][personToID[targetName]] = affinityValue;
    }
}

void addYourself(std::vector<std::vector<int>>& affinityMatrix, std::unordered_map<std::string, int>& personToID)
{
    personToID["me"] = affinityMatrix.size();
    std::ranges::for_each(affinityMatrix, [](std::vector<int>& affinities){ affinities.push_back(0); });
    affinityMatrix.push_back({});
    affinityMatrix[personToID["me"]].resize(personToID.size());
    std::ranges::for_each(affinityMatrix[personToID["me"]], [](int& affinity){ affinity = 0; });
}

int calculateMaxHappiness(const std::vector<std::vector<int>>& affinityMatrix, const std::unordered_map<std::string, int>& personToID, std::vector<int> table, const int personID)
{
    table.push_back(personID);
    if(table.size() == personToID.size()) 
    {
        const auto happiness = [&](const std::tuple<int, int> peopleIDs) {
            const auto [a, b] = peopleIDs;
            return affinityMatrix[a][b] + affinityMatrix[b][a];
        };
        table.push_back(table[0]); //Closing the circle
        return std::ranges::fold_left(table | std::views::adjacent<2> | std::views::transform(happiness), 0, std::plus<int>());
    }

    std::vector<int> affinityValues;
    std::ranges::for_each(std::views::iota(0, static_cast<int>(personToID.size())), [&](const int personID){ if(std::ranges::find(table, personID) == table.end()) affinityValues.push_back(calculateMaxHappiness(affinityMatrix, personToID, table, personID)); });
    return std::ranges::max(affinityValues);
}

int main(int argc, char **argv)
{
    std::string sentence;
    std::vector<std::vector<int>> affinityMatrix;
    std::unordered_map<std::string, int> personToID;
    std::vector<int> table;

    while(std::getline(std::cin, sentence)) loadAffinityMatrix(sentence, affinityMatrix, personToID);
    addYourself(affinityMatrix, personToID);
    std::cout << "Max Happiness: " << calculateMaxHappiness(affinityMatrix, personToID, table, 0) << std::endl;

}