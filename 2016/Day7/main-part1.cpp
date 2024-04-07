#include <iostream>
#include <string>
#include <ranges>
#include <vector>

int main(int argc, char **argv)
{
    std::string IP;
    int validIPs{0};
    const std::string blank = " ";
    const auto hasABBA = [](const auto& tuple){ return (std::get<0>(tuple) == std::get<3>(tuple) && std::get<1>(tuple) == std::get<2>(tuple) && std::get<0>(tuple) != std::get<1>(tuple)); };
    
    while(std::cin >> IP)
    {
        while(IP.contains('['))
        {
            const auto hypernetStart{IP.find('[')};
            const auto hypernetEnd{IP.find(']')};
            const long long unsigned int hypernetSize{hypernetEnd - hypernetStart + 1};
            const std::string hypernet{IP.substr(hypernetStart + 1, hypernetSize - 2)};
            auto ABBAInHypernetSequence = hypernet | std::views::adjacent<4> | std::views::filter(hasABBA);
            IP = ABBAInHypernetSequence.empty() ? IP.erase(hypernetStart, hypernetSize) : std::string();
            if(!IP.empty()) IP.insert(hypernetStart, blank.c_str());
        }
        auto ABBAInIP = IP | std::views::adjacent<4> | std::views::filter(hasABBA);
        if(!ABBAInIP.empty()) ++validIPs;
    }

    std::cout << "IPs supporting TLS: " << validIPs << std::endl;       
}