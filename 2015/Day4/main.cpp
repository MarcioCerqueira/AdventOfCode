#include <iostream>
#include <string>
#include <ranges>
#include "md5.h"

int main(int argc, char **argv)
{
    std::string secretKey;
    std::getline(std::cin, secretKey);

    auto findDecimal = [&secretKey](const int number){ return md5((secretKey + std::to_string(number)).c_str()).starts_with("000000"); };
    std::cout << "Answer: " << (std::views::iota(0) | std::views::filter(findDecimal) | std::views::take(0)).front() << std::endl;
}