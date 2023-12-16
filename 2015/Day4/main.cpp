#include <iostream>
#include <string>
#include "md5.h"

int main(int argc, char **argv)
{
    std::string secretKey;
    std::getline(std::cin, secretKey);

    int number = 0;
    while(md5((secretKey + std::to_string(number)).c_str()).substr(0, 6) != "000000")
    {
        number++;
    }
    std::cout << "Answer: " << number << std::endl;
}