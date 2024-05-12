#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <ranges>

long long int getDecompressedFileSize(const std::string& compressedFile)
{
    bool isMarkerActive{false};
    bool leftNumberMustBeFilled{false};
    std::string decompressedFile, leftNumberAsString, rightNumberAsString, decompressedString;
    int leftNumber{0}, rightNumber{0};
    long long int decompressedFileSize{0};
    for(int index = 0; index < compressedFile.size(); ++index) {
        const char character = compressedFile[index];
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
                decompressedFileSize += rightNumber * getDecompressedFileSize(compressedFile.substr(index, leftNumber));
                index += leftNumber - 1;
                leftNumber = 0;
                rightNumber = 0;
            } else {
                if(character == '(') {
                    isMarkerActive = true;
                    leftNumberMustBeFilled = true;
                } else {
                    ++decompressedFileSize;
                }
            }
        } 
    };
    return decompressedFileSize;
}

int main(int argc, char **argv)
{
    std::string compressedFile;
    std::ifstream file("file.txt");
    file >> compressedFile;
    //std::cin >> compressedFile;
    std::cout << "Decompressed length: " << getDecompressedFileSize(compressedFile) << std::endl;
}