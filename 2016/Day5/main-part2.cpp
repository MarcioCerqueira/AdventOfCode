#include <iostream>
#include <string>
#include <ranges>
#include <algorithm>
#include "md5.h"

int main(int argc, char **argv)
{
    std::string secretKey, password;
    std::getline(std::cin, secretKey);
    password.resize(10);

    const auto findDecimal = [&secretKey](const int number){ 
        return md5((secretKey + std::to_string(number)).c_str()).starts_with("00000"); 
    };
    const auto findValidPosition = [&secretKey, &password](const int number){
        const std::string hash{md5((secretKey + std::to_string(number)).c_str())};
        if(isdigit(hash[5])) {
            int digit = hash[5] - '0'; 
            if(digit >= 8 || isalpha(password[digit]) || isdigit(password[digit])) return false;
            else {
                password[digit] = hash[6];
                return true;
            }
        } else return false;
    };
    const auto returnCharacter = [&secretKey](const int number){ 
        const std::string hash{md5((secretKey + std::to_string(number)).c_str())};
        return std::make_pair(hash[5] - '0', hash[6]);
    };
    const auto print = [&password](const std::pair<int, char>& pair){
        password[pair.first] = pair.second; 
        std::cout << password << std::endl;
    };
    std::ranges::for_each(std::views::iota(0) | std::views::filter(findDecimal) 
                          | std::views::filter(findValidPosition) | std::views::transform(returnCharacter) 
                          | std::views::take(8), print);
    std::cout << password << std::endl;
}