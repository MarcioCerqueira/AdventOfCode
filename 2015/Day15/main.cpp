#include <iostream>
#include <regex>
#include <string>
#include <optional>
#include <ranges>
#include <algorithm>

struct Ingredient
{
    std::string name;
    int capacity;
    int durability;
    int flavor;
    int texture;
    int calories;
};

std::vector<Ingredient> loadIngredients()
{
    std::vector<Ingredient> ingredients;
    std::string ingredientDescription;
    while(std::getline(std::cin, ingredientDescription))
    {
        const std::regex sentenceRegex("(\\w+): capacity (-?\\d+), durability (-?\\d+), flavor (-?\\d+), texture (-?\\d+), calories (-?\\d+)");
        std::smatch stringMatch;
        std::regex_search(ingredientDescription, stringMatch, sentenceRegex);
        Ingredient ingredient {
            .name = stringMatch.str(1),
            .capacity = std::stoi(stringMatch.str(2)),
            .durability = std::stoi(stringMatch.str(3)),
            .flavor = std::stoi(stringMatch.str(4)),
            .texture = std::stoi(stringMatch.str(5)),
            .calories = std::stoi(stringMatch.str(6))
        };
        ingredients.push_back(ingredient);
    }
    return ingredients;
}

long long int estimateScore(const std::vector<Ingredient>& ingredients, const std::vector<int>& quantities)
{
    const auto mix = std::views::zip(ingredients, quantities);
    const auto toCaloriesProduct = [](const auto tuple){ return std::get<0>(tuple).calories * std::get<1>(tuple); };
    const auto toCapacityProduct = [](const auto tuple){ return std::get<0>(tuple).capacity * std::get<1>(tuple); };
    const auto toDurabilityProduct = [](const auto tuple){ return std::get<0>(tuple).durability * std::get<1>(tuple); };
    const auto toFlavorProduct = [](const auto tuple){ return std::get<0>(tuple).flavor * std::get<1>(tuple); };
    const auto toTextureProduct = [](const auto tuple){ return std::get<0>(tuple).texture * std::get<1>(tuple); };
    
    const int caloriesSum = std::ranges::fold_left(mix | std::views::transform(toCaloriesProduct), 0, std::plus<int>());
    if(caloriesSum != 500) return 0;
    
    const int capacitySum = std::ranges::fold_left(mix | std::views::transform(toCapacityProduct), 0, std::plus<int>());
    const int durabilitySum = std::ranges::fold_left(mix | std::views::transform(toDurabilityProduct), 0, std::plus<int>());
    const int flavorSum = std::ranges::fold_left(mix | std::views::transform(toFlavorProduct), 0, std::plus<int>());
    const int textureSum = std::ranges::fold_left(mix | std::views::transform(toTextureProduct), 0, std::plus<int>());

    long long int sum = 1 * std::max(0, capacitySum) * std::max(0, durabilitySum) * std::max(0, flavorSum) * std::max(0, textureSum);
    return sum;
}

long long int estimateBestScore(const std::vector<Ingredient>& ingredients, const int maxQuantity, std::vector<int> quantities = {})
{
    if(ingredients.size() == quantities.size())
    {
        return estimateScore(ingredients, quantities);
    }

    std::optional<long long int> max;
    std::ranges::for_each(std::views::iota(0, maxQuantity + 1), [&](const int baseQuantity){
        quantities.push_back(baseQuantity);
        long long int sum = estimateBestScore(ingredients, maxQuantity - baseQuantity, quantities);
        quantities.pop_back();
        if(!max.has_value() || sum > max) max = sum;
    });
    return max.value(); 
}

int main(int argc, char **argv)
{
    const int maxQuantity{100};
    const std::vector<Ingredient> ingredients { loadIngredients() };
    std::cout << "Total Score: " << estimateBestScore(ingredients, maxQuantity) << std::endl;
}