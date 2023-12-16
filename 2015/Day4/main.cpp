#include <iostream>
#include <string>
#include "md5.h"

int main(int argc, char **argv)
{
    std::string secretKey;
    std::getline(std::cin, secretKey);

    int number = 0;
    while(!md5((secretKey + std::to_string(number)).c_str()).starts_with("000000"))
    {
        number++;
    }
    std::cout << "Answer: " << number << std::endl;
}