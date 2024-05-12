#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <ranges>

int main(int argc, char **argv)
{
    std::string compressedFile;
    std::ifstream file("file.txt");
    file >> compressedFile;
    //std::cin >> compressedFile;
    
    bool isMarkerActive{false};
    bool leftNumberMustBeFilled{false};
    std::string decompressedFile, leftNumberAsString, rightNumberAsString, decompressedString;
    int leftNumber{0}, rightNumber{0};
    std::ranges::for_each(compressedFile, [&](const char character){
        if(isMarkerActive) {
            if(character == 'x') {
                leftNumberMustBeFilled = false;
                leftNumber = atoi(leftNumberAsString.c_str());
                leftNumberAsString.clear();
            } else if(character == ')') {
                isMarkerActive = false;
                leftNumberMustBeFilled = false;
                rightNumber = atoi(rightNumberAsString.c_str());
                rightNumberAsString.clear();
            } else if(leftNumberMustBeFilled) {
                leftNumberAsString += character;
            } else {
                rightNumberAsString += character;
            }
        } else {
            if(leftNumber > 0) {
                decompressedString += character;
                --leftNumber;
                if(leftNumber == 0) {
                    std::ranges::for_each(std::views::iota(0, rightNumber), [&](const int index){
                        decompressedFile.append(decompressedString);
                    });
                    rightNumber = 0;
                    decompressedString.clear();
                }
            } else {
                if(character == '(') {
                    isMarkerActive = true;
                    leftNumberMustBeFilled = true;
                } else {
                    decompressedFile += character;
                }
            }
        } 
    });
    std::cout << "Decompressed length: " << decompressedFile.size() << std::endl;
}