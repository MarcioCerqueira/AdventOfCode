#include <iostream>
#include <sstream>

int main(int argc, char **argv)
{
    std::string dimensions;
    int totalSquare = 0;
    int totalRibbon = 0;
    
    while(std::cin >> dimensions)
    {
        std::stringstream stringStream(dimensions);
        std::string length, width, height;
        std::getline(stringStream, length, 'x');
        std::getline(stringStream, width, 'x');
        std::getline(stringStream, height, 'x');

        const int l = std::stoi(length);
        const int w = std::stoi(width);
        const int h = std::stoi(height);

        const int lw = l * w;
        const int lh = l * h;
        const int wh = w * h;
        
        const int square = 2 * lw + 2 * lh + 2 * wh + std::min<int>(std::min<int>(lw, lh), wh);
        const int ribbon = l * w * h + 2 * l + 2 * w + 2 * h - 2 * std::max<int>(std::max<int>(l, w), h);
        
        totalSquare += square;
        totalRibbon += ribbon;
    }

    std::cout << "Total Square: " << totalSquare << std::endl;
    std::cout << "Total Ribbon: " << totalRibbon << std::endl;
    return 0;
}