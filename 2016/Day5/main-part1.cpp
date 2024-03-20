#include <iostream>
#include <string>
#include <ranges>
#include <algorithm>
#include "md5.h"

int main(int argc, char **argv)
{
    std::string secretKey;
    std::getline(std::cin, secretKey);

    auto findDecimal = [&secretKey](const int number){ return md5((secretKey + std::to_string(number)).c_str()).starts_with("00000"); };
    auto returnCharacter = [&secretKey](const int number){ return md5((secretKey + std::to_string(number)).c_str()).at(5); };
    auto print = [](const char x){ std::cout << x;};
    std::ranges::for_each(std::views::iota(0) | std::views::filter(findDecimal) | std::views::transform(returnCharacter) | std::views::take(8), print);
}