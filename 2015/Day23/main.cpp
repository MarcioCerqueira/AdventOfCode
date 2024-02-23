#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>

int main(int argc, char **argv)
{
    std::unordered_map<std::string, int> registers;
    registers["a"] = 1;
    registers["b"] = 0;

    std::vector<std::string> instructions;
    std::string instruction;
    while(std::getline(std::cin, instruction))
    {
        instructions.push_back(instruction);
    }

    std::string command, target, tmp;
    for(int index = 0; index < instructions.size(); index++)
    {
        std::stringstream stringStream(instructions[index]);
        stringStream >> command;
        if(command == "hlf") 
        {
            stringStream >> target;
            registers[target] /= 2;
        }
        else if(command == "tpl")
        {
            stringStream >> target;
            registers[target] *= 3;
        } 
        else if(command == "inc")
        {
            stringStream >> target;
            registers[target]++;
        }
        else if(command == "jmp")
        {
            stringStream >> tmp;
            index += atoi(tmp.c_str()) - 1;
        }
        else if(command == "jie")
        {
            stringStream >> tmp;
            std::string reg;
            reg = tmp[0];
            if(registers[reg] % 2 == 0) 
            {
                stringStream >> tmp;
                index += atoi(tmp.c_str()) - 1;
            }
        }
        else if(command == "jio")
        {
            stringStream >> tmp;
            std::string reg;
            reg = tmp[0];
            if(registers[reg] == 1) 
            {
                stringStream >> tmp;
                index += atoi(tmp.c_str()) - 1;
            }
        }
    }

    std::cout << "Register b has value: " << registers["b"] << std::endl;
}