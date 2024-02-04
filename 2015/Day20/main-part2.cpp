#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <cmath>
#include <set>

//50 -> 50, 25, 10, 5, 2, 1
//100 -> 100, 50, 25, 20, 5, 4, 2, (1)
//200 -> 200, 100, 50, 25, 20, 10, 8, 4, (2), (1)
int main(int argc, char **argv)
{
    const int presentsDeliveredPerElf{11};
    
    int presents;
    std::cin >> presents;
    
    //for(int houseNumber = std::max<int>(presents / 50, 1); houseNumber <= presents/presentsDeliveredPerElf; houseNumber++)
    for(int houseNumber = 1; houseNumber <= presents/presentsDeliveredPerElf; houseNumber++)
    {
        int partialSum = 0;
        std::set<int> numbersAlreadyUsed;
        //for(int number = houseNumber; number >= std::max<int>(houseNumber / 50, 1); number--)
        for(int number = 1; number <= sqrt(houseNumber); number++)
        {
            if(numbersAlreadyUsed.contains(number)) 
            {
                continue;
            }

            if(houseNumber % number == 0) 
            {
                if(houseNumber / number <= 50)
                {
                    partialSum += number * presentsDeliveredPerElf;
                    numbersAlreadyUsed.insert(number);
                }
                int result = houseNumber / number;
                if(!numbersAlreadyUsed.contains(result) && houseNumber / result <= 50)
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