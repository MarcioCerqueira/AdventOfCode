#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <ranges>
#include <numeric>

std::map<int, int> countOfFilledContainers;

int fillContainers(int currentLitersOfEggnog, const int maxLitersOfEggnog, int index, 
    std::vector<int> containers, std::vector<bool> usedContainers)
{
    if(currentLitersOfEggnog > maxLitersOfEggnog) 
    {
        return 0;
    }

    if(currentLitersOfEggnog == maxLitersOfEggnog) 
    {
        countOfFilledContainers[std::ranges::fold_left(usedContainers, 0, std::plus<int>())]++;
        return 1;
    }

    return std::ranges::fold_left(std::views::iota(index, static_cast<int>(containers.size()) + 1), 0, [&](int initialValue, int index){
        if(!usedContainers[index]) 
        {
            usedContainers[index] = true;
            int sum = fillContainers(currentLitersOfEggnog + containers[index], maxLitersOfEggnog, index, containers, usedContainers);
            usedContainers[index] = false;
            return initialValue + sum;
        }
        return initialValue;
    });
}

int main(int argc, char **argv)
{
    const int maxLitersOfEggnog{150};
    int currentLitersOfEggnog{0};
    
    std::vector<int> containers;
    std::vector<bool> usedContainers;
    int container;
    while(std::cin >> container) 
    {
        containers.push_back(container);
        usedContainers.push_back(false);
    }

    std::cout << "Different combination of containers: " << fillContainers(currentLitersOfEggnog, maxLitersOfEggnog, 0, containers, usedContainers) << std::endl;
    std::cout << "We can combine " << countOfFilledContainers.begin()->first << " elements in " << countOfFilledContainers.begin()->second << " different ways." << std::endl;
}