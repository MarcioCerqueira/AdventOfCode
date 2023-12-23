#include <iostream>
#include <string>
#include <algorithm>

int main(int argc, char **argv)
{
    std::string stringLiteral;
    int charactersOfCodeOriginal{0}, charactersOfCodeEncoded{0}, charactersOfMemoryOriginal{0};
    while(std::getline(std::cin, stringLiteral))
    {
        charactersOfCodeOriginal += stringLiteral.length();
        
        std::string encodedString;
        encodedString += '"';
        std::ranges::for_each(stringLiteral, [&encodedString](const auto character){
            if(character == '"' || character == '\\') encodedString += "\\";
            encodedString += character;
        });
        encodedString += '"';
        
        for(int character = 0; character < charactersOfCodeOriginal - 1; character++)
        {
            if(character >= stringLiteral.size()) break;
            if(stringLiteral[character] == '\\' && stringLiteral[character + 1] == '\\') stringLiteral.replace(character, 2, "a");
            else if(stringLiteral[character] == '\\' && stringLiteral[character + 1] == '"') stringLiteral.replace(character, 2, "b");
            else if(stringLiteral[character] == '\\' && stringLiteral[character + 1] == 'x') stringLiteral.replace(character, 4, "c");
        }
        const auto result = std::ranges::remove(stringLiteral, '"');
        stringLiteral.erase(result.begin(), result.end());
        
        charactersOfMemoryOriginal += stringLiteral.length();
        charactersOfCodeEncoded += encodedString.length();
    }

    std::cout << "Answer (Part I): " << charactersOfCodeOriginal - charactersOfMemoryOriginal << std::endl;
    std::cout << "Answer (Part II): " << charactersOfCodeEncoded - charactersOfCodeOriginal << std::endl;
}