#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <cmath>
#include <set>

int main(int argc, char **argv)
{
    const int presentsDeliveredPerElf{10};
    
    int presents;
    std::cin >> presents;
    
    for(int houseNumber = 1; houseNumber <= presents/presentsDeliveredPerElf; houseNumber++)
    {
        int partialSum = 0;
        std::set<int> numbersAlreadyUsed;
        for(int number = 1; number <= sqrt(houseNumber); number++)
        {
            if(numbersAlreadyUsed.contains(number)) 
            {
                continue;
            }

            if(houseNumber % number == 0) 
            {
                partialSum += number * presentsDeliveredPerElf;
                numbersAlreadyUsed.insert(number);
                
                int result = houseNumber / number;
                if(!numbersAlreadyUsed.contains(result))
                {
                    partialSum += result * presentsDeliveredPerElf;
                    numbersAlreadyUsed.insert(result);
                }
            }
            if(partialSum >= presents) 
            {
                std::cout << "Lowest House Number is: " << houseNumber << std::endl;
                return 0;
            }
        }
    }    
}