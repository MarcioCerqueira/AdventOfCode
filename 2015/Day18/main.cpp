#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

int main(int argc, char **argv)
{
    std::vector<std::vector<char>> lights, transformedLights;
    std::string rowConfiguration;

    while(std::cin >> rowConfiguration)
    {
        std::vector<char> row;
        std::ranges::for_each(rowConfiguration, [&row](const char c){ row.push_back(c); });
        lights.push_back(row);
    }

    lights[0][0] = '#';
    lights[0][lights[0].size() - 1] = '#';
    lights[lights.size() - 1][0] = '#';
    lights[lights.size() - 1][lights[0].size() - 1] = '#';

    transformedLights = lights;
    const int steps{100};
    std::ranges::for_each(std::views::iota(0, steps), [&](const int step) {
        std::ranges::for_each(std::views::iota(0, static_cast<int>(lights.size())), [&](const int row){
            std::ranges::for_each(std::views::iota(0, static_cast<int>(lights[0].size())), [&](const int col){
                int sum = 0;
                if(row - 1 >= 0 && col - 1 >= 0 && lights[row - 1][col - 1] == '#') sum++;
                if(row - 1 >= 0 && lights[row - 1][col] == '#') sum++;
                if(row - 1 >= 0 && col + 1 < lights[0].size() && lights[row - 1][col + 1] == '#') sum++;
                if(col - 1 >= 0 && lights[row][col - 1] == '#') sum++;
                if(col + 1 < lights[0].size() && lights[row][col + 1] == '#') sum++;
                if(row + 1 < lights.size() && col - 1 >= 0 && lights[row + 1][col - 1] == '#') sum++;
                if(row + 1 < lights.size() && lights[row + 1][col] == '#') sum++;
                if(row + 1 < lights.size() && col + 1 < lights[0].size() && lights[row + 1][col + 1] == '#') sum++;

                if(row == 0 && col == 0) transformedLights[row][col] = '#';
                else if(row == 0 && col == lights[0].size() - 1) transformedLights[row][col] = '#';
                else if(row == lights.size() - 1 && col == 0) transformedLights[row][col] = '#';
                else if(row == lights.size() - 1 && col == lights[0].size() - 1) transformedLights[row][col] = '#';
                else if(lights[row][col] == '#' && (sum == 2 || sum == 3)) transformedLights[row][col] = '#';
                else if(lights[row][col] == '.' && sum == 3) transformedLights[row][col] = '#';
                else transformedLights[row][col] = '.';
            });
        });
        lights = transformedLights;
    });

    const int lightsOn = std::ranges::fold_left(lights, 0, [](int a, const auto& row){ 
        return a + std::ranges::fold_left(row, 0, [](int b, const char light){ 
            return light == '#' ? b + 1: b;
        });
    });
    std::cout << "There are " << lightsOn << " lights on" << std::endl;
}