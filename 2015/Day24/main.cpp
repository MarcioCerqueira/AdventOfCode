#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

std::vector<int> loadWeights()
{
    int weight;
    std::vector<int> weights;
    while(std::cin >> weight) weights.push_back(weight);
    return weights;
}

std::vector<std::vector<int>> generateCombinations(const std::vector<int>& weights, const int numberOfElements)
{
    std::vector<bool> selector(weights.size());
    std::ranges::fill_n(selector.begin(), numberOfElements, true);
    std::vector<std::vector<int>> combinations;
    do {
        std::vector<int> combination;
        const auto insertCombination = [&](const auto& tuple){ if(std::get<0>(tuple)) combination.push_back(std::get<1>(tuple)); };
        std::ranges::for_each(std::views::zip(selector, weights), insertCombination);
        combinations.push_back(combination);
    } while(std::prev_permutation(selector.begin(), selector.end()));
    return combinations;
} 

int main(int argc, char **argv)
{
    const std::vector<int> weights{loadWeights()};
    const int totalWeight{std::ranges::fold_left(weights, 0, std::plus<int>())};
    
    int numberOfPackages{1};
    std::vector<std::vector<int>> combinations;
    const auto isValid = [&](const auto combination){ return std::ranges::fold_left(combination, 0, std::plus<int>()) == totalWeight/4; };
    do {
        combinations = generateCombinations(weights, numberOfPackages);
        ++numberOfPackages;
    } while(!std::ranges::any_of(combinations, isValid));

    const auto toQuantumEntanglement = [&](const auto combination) { return std::ranges::fold_left(combination, 1, std::multiplies<unsigned long long int>()); };
    std::cout << "Quantum Entanglement: " << std::ranges::min(combinations | std::views::filter(isValid) | std::views::transform(toQuantumEntanglement)) << std::endl;
    return 0;
}