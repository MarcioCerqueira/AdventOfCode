#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <ranges>
#include <algorithm>
#include <regex>

struct Node
{
    std::string name;
    std::vector<std::shared_ptr<Node>> neighbours;
    std::vector<int> distances;
};

enum class Rule
{
    Min,
    Max
};

void insertNodeInGraph(std::unordered_map<std::string, std::shared_ptr<Node>>& graph, const std::string& name)
{
    std::shared_ptr<Node> node = std::make_shared<Node>();
    node->name = name;
    graph[name] = node;
}

int getDistance(std::unordered_map<std::string, std::shared_ptr<Node>> graph, std::unordered_map<std::string, bool> visited, int currentDistance, const std::string& name, Rule rule)
{
    std::vector<int> distances;
    visited[name] = true;
    std::ranges::for_each(std::views::zip(graph[name]->neighbours, graph[name]->distances), [&](auto element){
        if(!visited[std::get<0>(element)->name]) distances.push_back(getDistance(graph, visited, currentDistance + std::get<1>(element), std::get<0>(element)->name, rule));
    });
    if(rule == Rule::Min) return distances.empty() ? currentDistance : std::ranges::min(distances);
    return distances.empty() ? currentDistance : std::ranges::max(distances);
}

int main(int argc, char **argv)
{
    std::unordered_map<std::string, std::shared_ptr<Node>> graph;
    std::unordered_map<std::string, bool> visited;
    std::string info, sourceName, to, targetName, equals, distance;
        
    while(std::getline(std::cin, info))
    {
        const std::regex sentenceRegex("(\\w+) to (\\w+) = (\\d+)");
        std::smatch stringMatch;
        std::regex_search(info, stringMatch, sentenceRegex);
        
        const std::string sourceName{stringMatch.str(1)};
        const std::string targetName{stringMatch.str(2)};
        const int distance{stoi(stringMatch.str(3))};
        
        if(!graph.contains(sourceName)) insertNodeInGraph(graph, sourceName);
        if(!graph.contains(targetName)) insertNodeInGraph(graph, targetName);

        graph[sourceName]->neighbours.push_back(graph[targetName]);
        graph[sourceName]->distances.push_back(distance);
        visited[sourceName] = false;

        graph[targetName]->neighbours.push_back(graph[sourceName]);
        graph[targetName]->distances.push_back(distance);
        visited[targetName] = false;
    }
    
    std::vector<int> distances;
    std::ranges::for_each(graph, [&](auto pair){ distances.push_back(getDistance(graph, visited, 0, pair.second->name, Rule::Min)); });
    std::cout << "The distance of the shortest route is: " << std::ranges::min(distances) << std::endl;
    
    distances.clear();
    std::ranges::for_each(graph, [&](auto pair){ distances.push_back(getDistance(graph, visited, 0, pair.second->name, Rule::Max)); });
    std::cout << "The distance of the longest route is: " << std::ranges::max(distances) << std::endl;
    return 0;
}