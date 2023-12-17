#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <ranges>

int main(int argc, char** argv)
{
    std::string instructions;
    std::cin >> instructions;

    auto transformInstruction = [](const char instruction){ return instruction == '(' ? 1 : -1; };
    auto integerInstructions = instructions | std::views::transform(transformInstruction);
    
    std::vector<int> floors(integerInstructions.size());
    std::partial_sum(integerInstructions.begin(), integerInstructions.end(), floors.begin());
    
    std::vector<int> negativeFloor{-1};
    auto result = std::ranges::find_first_of(floors, negativeFloor);
    
    std::cout << "Final Floor: " << floors.back() << std::endl;
    if(result != floors.end()) std::cout << "Position: " << std::distance(floors.begin(), result) + 1 << std::endl;
    return 0;
}