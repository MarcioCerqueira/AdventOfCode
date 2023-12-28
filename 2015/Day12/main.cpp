#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ranges>
#include <rapidjson/document.h>

int traverse(const rapidjson::Value& JSON)
{
    int sum{0};
    if(JSON.IsArray())
    {
        for(auto& object : JSON.GetArray())
        {
            if(object.IsObject() || object.IsArray()) sum += traverse(object);
            else if(object.IsInt()) sum += object.GetInt();
        }
    }
    else if(JSON.IsObject())
    {
        for(auto& object : JSON.GetObject())
        {
            if(object.value.IsString() && strcmp(object.value.GetString(), "red") == 0) return 0;
            else if(object.value.IsObject() || object.value.IsArray()) sum += traverse(object.value);
            else if(object.value.IsInt()) sum += object.value.GetInt();
        }
    }
    else if(JSON.IsInt())
    {
        sum += JSON.GetInt();
    }
    return sum;
}

std::optional<std::string> loadFileContent(const std::string& filename)
{
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cout << "Failed to open " << filename << std::endl;
        return std::nullopt;
    }

    std::string partialContent, fullContent;
    while(file.good())
    {
        file >> partialContent;
        fullContent.append(partialContent);
    }

    return fullContent;
}

int main(int argc, char **argv)
{
    std::string filename;
    std::cin >> filename;
    
    std::optional<std::string> fileContent = loadFileContent(filename);
    if(!fileContent.has_value()) return -1;
    
    rapidjson::Document JSONDocument;
    JSONDocument.Parse(fileContent.value().c_str());   
    
    int sum{0};
    for(auto& object : JSONDocument.GetObject())
    {
        if(object.value.IsString() && strcmp(object.value.GetString(), "red") == 0) sum = 0;
        else if(object.value.IsObject() || object.value.IsArray()) sum += traverse(object.value);
        else if(object.value.IsInt()) sum += object.value.GetInt();
    }
    std::cout << "Sum: " << sum << std::endl;
}