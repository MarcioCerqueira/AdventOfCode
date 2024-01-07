#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <optional>
#include <ranges>
#include <algorithm>

struct AuntSueCompound
{
    std::optional<int> children;
    std::optional<int> cats;
    std::optional<int> samoyeds;
    std::optional<int> pomeranians;
    std::optional<int> akitas;
    std::optional<int> vizslas;
    std::optional<int> goldfish;
    std::optional<int> trees;
    std::optional<int> cars;
    std::optional<int> perfumes;
};

AuntSueCompound loadGroundTruthCompound()
{
    return AuntSueCompound{
        .children = 3,
        .cats = 7,
        .samoyeds = 2,
        .pomeranians = 3,
        .akitas = 0,
        .vizslas = 0,
        .goldfish = 5,
        .trees = 3,
        .cars = 2,
        .perfumes = 1
    };
}

std::vector<AuntSueCompound> loadPersonalListOfCompounds()
{
    std::vector<AuntSueCompound> compounds;
    std::string compoundDescription;
    const std::regex sentenceRegex("Sue (\\d+): (\\w+): (\\d+), (\\w+): (\\d+), (\\w+): (\\d+)");
    const std::vector<int> indices{2, 4, 6};
    while(std::getline(std::cin, compoundDescription))
    {
        std::smatch stringMatch;
        std::regex_search(compoundDescription, stringMatch, sentenceRegex);
        AuntSueCompound compound;
        std::ranges::for_each(indices, [&compound, &stringMatch](const int index) {
            if(stringMatch.str(index) == "children") compound.children = std::stoi(stringMatch.str(index + 1));
            else if(stringMatch.str(index) == "cats") compound.cats = std::stoi(stringMatch.str(index + 1));
            else if(stringMatch.str(index) == "samoyeds") compound.samoyeds = std::stoi(stringMatch.str(index + 1));
            else if(stringMatch.str(index) == "pomeranians") compound.pomeranians = std::stoi(stringMatch.str(index + 1));
            else if(stringMatch.str(index) == "akitas") compound.akitas = std::stoi(stringMatch.str(index + 1));
            else if(stringMatch.str(index) == "vizslas") compound.vizslas = std::stoi(stringMatch.str(index + 1));
            else if(stringMatch.str(index) == "goldfish") compound.goldfish = std::stoi(stringMatch.str(index + 1));
            else if(stringMatch.str(index) == "trees") compound.trees = std::stoi(stringMatch.str(index + 1));
            else if(stringMatch.str(index) == "cars") compound.cars = std::stoi(stringMatch.str(index + 1));
            else if(stringMatch.str(index) == "perfumes") compound.perfumes = std::stoi(stringMatch.str(index + 1));
        });
        compounds.push_back(compound);
    }
    return compounds;
}

int searchAuntSue(const AuntSueCompound& groundTruthCompound, const std::vector<AuntSueCompound>& auntSueCompounds)
{
    const auto result = std::ranges::find_if(auntSueCompounds, [groundTruthCompound](const AuntSueCompound& auntSueCompound){
        bool found = true;
        if(auntSueCompound.children.has_value() && auntSueCompound.children != groundTruthCompound.children) found = false;
        if(auntSueCompound.cats.has_value() && auntSueCompound.cats <= groundTruthCompound.cats) found = false;
        if(auntSueCompound.samoyeds.has_value() && auntSueCompound.samoyeds != groundTruthCompound.samoyeds) found = false;
        if(auntSueCompound.pomeranians.has_value() && auntSueCompound.pomeranians >= groundTruthCompound.pomeranians) found = false;
        if(auntSueCompound.akitas.has_value() && auntSueCompound.akitas != groundTruthCompound.akitas) found = false;
        if(auntSueCompound.vizslas.has_value() && auntSueCompound.vizslas != groundTruthCompound.vizslas) found = false;
        if(auntSueCompound.goldfish.has_value() && auntSueCompound.goldfish >= groundTruthCompound.goldfish) found = false;
        if(auntSueCompound.trees.has_value() && auntSueCompound.trees <= groundTruthCompound.trees) found = false;
        if(auntSueCompound.cars.has_value() && auntSueCompound.cars != groundTruthCompound.cars) found = false;
        if(auntSueCompound.perfumes.has_value() && auntSueCompound.perfumes != groundTruthCompound.perfumes) found = false;
        return found;
    });
    return std::distance(auntSueCompounds.begin(), result) + 1;
}

int main(int argc, char **argv)
{
    AuntSueCompound groundTruthCompound = loadGroundTruthCompound();
    std::vector<AuntSueCompound> auntSueCompounds = loadPersonalListOfCompounds();
    std::cout << "Aunt Sue #" << searchAuntSue(groundTruthCompound, auntSueCompounds) << " gifted me!" << std::endl;
}