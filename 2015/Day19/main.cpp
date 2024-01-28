#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <regex>
#include <vector>
#include <algorithm>
#include <ranges>

void loadReplacements(std::vector<std::pair<std::string, std::string>>& replacements)
{
    const std::regex sentenceRegex("(\\w+) => (\\w+)");
    std::string replacement;
    std::smatch stringMatch;
    while(std::getline(std::cin, replacement))
    {
        if(replacement.empty()) break;
        std::regex_search(replacement, stringMatch, sentenceRegex);
        replacements.push_back(std::make_pair(stringMatch.str(1), stringMatch.str(2)));
    }
}

void generateMolecules(const std::vector<std::pair<std::string, std::string>>& replacements,
std::string sentence, std::unordered_set<std::string>& uniqueMolecules)
{
    std::ranges::for_each(replacements, [&](const std::pair<std::string, std::string>& replacement){
        size_t pos = 0;
        do {
            auto posFound = sentence.find(replacement.first, pos);
            if(posFound == std::string::npos) break;
            std::string copy{sentence};
            uniqueMolecules.insert(copy.replace(posFound, replacement.first.size(), replacement.second));
            pos = posFound + 1;
        } while(true);
    });
}

int generateMedicine(const std::vector<std::pair<std::string, std::string>>& replacements, const std::string& sentence)
{
    const auto hasRn = [](const std::tuple<char, char>& pair) { return std::get<0>(pair) == 'R' && std::get<1>(pair) == 'n'; };
    const auto hasAr = [](const std::tuple<char, char>& pair) { return std::get<0>(pair) == 'A' && std::get<1>(pair) == 'r'; };
    const auto hasY = [](const char character){ return character == 'Y'; };
    const auto hasSymbol = [](const char character){ return isupper(character); };
    auto Rns = sentence | std::views::adjacent<2> | std::views::filter(hasRn);
    auto Ars = sentence | std::views::adjacent<2> | std::views::filter(hasAr);
    auto Ys = sentence | std::views::filter(hasY);
    auto symbols = sentence | std::views::filter(hasSymbol);
    
    return std::distance(symbols.begin(), symbols.end()) - std::distance(Rns.begin(), Rns.end()) - std::distance(Ars.begin(), Ars.end()) - 2 * std::distance(Ys.begin(), Ys.end()) - 1;
}

int main(int argc, char **argv)
{
    std::vector<std::pair<std::string, std::string>> replacements;
    loadReplacements(replacements);

    std::string sentence;
    std::cin >> sentence;

    std::unordered_set<std::string> uniqueMolecules;
    generateMolecules(replacements, sentence, uniqueMolecules);
    std::cout << "Unique molecules: " << uniqueMolecules.size() << std::endl;

    std::cout << "Minimum number of steps to generate the medicine: " << generateMedicine(replacements, sentence) << std::endl;
}