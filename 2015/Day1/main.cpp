#include <iostream>
#include <algorithm>
#include <optional>

int main(int argc, char** argv)
{
    std::string instructions;
    std::cin >> instructions;

    int position = 0;
    int finalFloor = 0;
    std::optional<int> basementPosition;
    for(char instruction : instructions)
    {
        position++;

        if(instruction == '(') finalFloor++;
        else finalFloor--;

        if(basementPosition.has_value()) continue;
        if(finalFloor < 0) basementPosition = position;
    }
    
    std::cout << "Floor: " << finalFloor << std::endl;
    if(basementPosition.has_value()) std::cout << "Position: " << basementPosition.value() << std::endl;
    return 0;
}