#include <iostream>
#include <vector>
#include <array>

bool isAPossibleTriangle(int a, int b, int c) 
{
    return a + b > c && b + c > a && c + a > b;
}

int main(int argc, char **argv)
{
    int a, b, c, possibleTrianglesInRow{0}, possibleTrianglesInCol{0};
    std::array<std::vector<int>, 3> cols;
    while(std::cin >> a >> b >> c)
    {
        possibleTrianglesInRow += isAPossibleTriangle(a, b, c) ? 1 : 0;
        cols[0].push_back(a);
        cols[1].push_back(b);
        cols[2].push_back(c);
        if(cols[0].size() == 3)
        {
            possibleTrianglesInCol += isAPossibleTriangle(cols[0][0], cols[0][1], cols[0][2]) ? 1 : 0;
            possibleTrianglesInCol += isAPossibleTriangle(cols[1][0], cols[1][1], cols[1][2]) ? 1 : 0;
            possibleTrianglesInCol += isAPossibleTriangle(cols[2][0], cols[2][1], cols[2][2]) ? 1 : 0;
            cols[0].clear();
            cols[1].clear();
            cols[2].clear();
        }
    }
    std::cout << "Number of possible triangles organized horizontally: " << possibleTrianglesInRow << std::endl;
    std::cout << "Number of possible triangles organized vertically: " << possibleTrianglesInCol << std::endl;
}