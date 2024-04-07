#include <iostream>
#include <string>
#include <ranges>
#include <vector>
#include <set>
#include <algorithm>

int main(int argc, char **argv)
{
    std::string IP;
    int validIPs{0};
    const std::string blank = " ";
    const auto isABA = [](const auto& tuple){ return (std::get<0>(tuple) == std::get<2>(tuple) && std::get<1>(tuple) != std::get<2>(tuple)); };
    
    while(std::cin >> IP)
    {
        std::set<std::tuple<char, char, char>> hypernetBABs;
        std::vector<std::tuple<char, char, char>> IPABAs;
        const auto insertBABsInHypernetSet = [&](const auto& tuple){ hypernetBABs.insert(std::tuple<char, char, char>(std::get<1>(tuple), std::get<0>(tuple), std::get<1>(tuple))); };
        const auto insertABAsInIPSet = [&](const auto& tuple){ IPABAs.push_back(tuple); };
        const auto hasBABInHypernet = [&](const auto& tuple){ return hypernetBABs.contains(tuple); };
        while(IP.contains('['))
        {
            const auto hypernetStart{IP.find('[')};
            const auto hypernetEnd{IP.find(']')};
            const long long unsigned int hypernetSize{hypernetEnd - hypernetStart + 1};
            const std::string hypernet{IP.substr(hypernetStart + 1, hypernetSize - 2)};
            auto ABAInHypernetSequence = hypernet | std::views::adjacent<3> | std::views::filter(isABA);
            std::ranges::for_each(ABAInHypernetSequence, insertBABsInHypernetSet);
            IP = IP.erase(hypernetStart, hypernetSize);
            IP.insert(hypernetStart, blank.c_str());
        }
        auto ABAInIP = IP | std::views::adjacent<3> | std::views::filter(isABA);
        std::ranges::for_each(ABAInIP, insertABAsInIPSet);
        if(std::ranges::any_of(IPABAs, hasBABInHypernet)) ++validIPs;
    }

    std::cout << "IPs supporting TLS: " << validIPs << std::endl;       
}