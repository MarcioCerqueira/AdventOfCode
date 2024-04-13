#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <ranges>
#include <numeric>

void print(const std::vector<std::vector<int>>& pixels)
{
    std::ranges::for_each(pixels, [&](const auto& row){
        std::ranges::for_each(std::views::iota(0, static_cast<int>(row.size())), [&](const int index){
            if(index % 5 == 0) std::cout << " ";
            std::cout << row[index];
        });
        std::cout << std::endl;
    });
}

int main(int argc, char **argv)
{
    const int numberOfRows = 6;
    const int numberOfCols = 50;

    std::vector<std::vector<int>> pixels;
    pixels.resize(numberOfRows);
    std::ranges::for_each(pixels, [](auto& row){ row.resize(numberOfCols); });

    const std::regex rectRegex("rect (\\d+)x(\\d+)");
    const std::regex rotateRowRegex("rotate row y=(\\d+) by (\\d+)");
    const std::regex rotateColumnRegex("rotate column x=(\\d+) by (\\d+)");
    std::smatch stringMatch;
    
    std::string instruction;
    while(std::getline(std::cin, instruction))
    {
        if(instruction.contains("rect"))
        {
            std::regex_search(instruction, stringMatch, rectRegex);
            const int A{stoi(stringMatch.str(1))};
            const int B{stoi(stringMatch.str(2))};
            std::ranges::for_each(std::views::iota(0, A), [&](const int row){
                std::ranges::for_each(std::views::iota(0, B), [&](const int col){
                    pixels[col][row] = true;
                });
            });
        }
        else if(instruction.contains("row"))
        {
            std::regex_search(instruction, stringMatch, rotateRowRegex);
            const int A{stoi(stringMatch.str(1))};
            const int B{stoi(stringMatch.str(2))};

            std::vector<int> row;
            std::ranges::for_each(pixels[A], [&](const auto& elem){ row.push_back(elem); });
            std::vector<int> indices(numberOfCols);
            std::ranges::iota(indices, 0);
            std::ranges::rotate(indices, indices.end() - B);
            std::ranges::for_each(std::views::iota(0, numberOfCols), [&](const int& index){ pixels[A][index] = row[indices[index]]; });
        }
        else
        {
            std::regex_search(instruction, stringMatch, rotateColumnRegex);
            const int A{stoi(stringMatch.str(1))};
            const int B{stoi(stringMatch.str(2))};

            std::vector<int> column;
            std::ranges::for_each(pixels, [&](const auto& row){ column.push_back(row[A]); });
            std::vector<int> indices(numberOfRows);
            std::ranges::iota(indices, 0);
            std::ranges::rotate(indices, indices.end() - B);
            std::ranges::for_each(std::views::iota(0, numberOfRows), [&](const int& index){ pixels[index][A] = column[indices[index]]; });
        }
    }

    const int litPixels = std::ranges::fold_left(pixels, 0, [](int a, const auto& row){ 
        return a + std::ranges::fold_left(row, 0, [](int b, const int elem){ 
            return b + elem;
        });
    });
    std::cout << "Lit pixels: " << litPixels << std::endl;
    print(pixels);
}