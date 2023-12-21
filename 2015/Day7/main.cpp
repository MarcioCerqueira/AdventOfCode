#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cstdint>
#include <memory>

struct Node
{
    std::optional<uint16_t> value;
    std::optional<std::string> operation;
    std::optional<std::string> leftNeighbourID;
    std::optional<std::string> rightNeighbourID;
};

void traverseGraph(std::unordered_map<std::string, Node>& wires)
{
    const auto allNodesVisited = [](const auto& pair){ return pair.second.value.has_value(); };
    while(!std::ranges::all_of(wires, allNodesVisited))
    {
        std::ranges::for_each(wires, [&wires](auto& pair){
            std::optional<std::string> leftNeighbourID = pair.second.leftNeighbourID;
            std::optional<std::string> rightNeighbourID = pair.second.rightNeighbourID;
            if(pair.second.value.has_value()) return;
            if(leftNeighbourID.has_value() && !wires[leftNeighbourID.value()].value.has_value()) return;
            if(rightNeighbourID.has_value() && !wires[rightNeighbourID.value()].value.has_value()) return;

            if(pair.second.operation == "ASSIGNMENT") pair.second.value = wires[leftNeighbourID.value()].value.value();
            else if(pair.second.operation == "NOT") pair.second.value = ~wires[leftNeighbourID.value()].value.value();
            else if(pair.second.operation == "AND") pair.second.value = wires[leftNeighbourID.value()].value.value() & wires[rightNeighbourID.value()].value.value();
            else if(pair.second.operation == "OR") pair.second.value = wires[leftNeighbourID.value()].value.value() | wires[rightNeighbourID.value()].value.value();
            else if(pair.second.operation == "LSHIFT") pair.second.value = wires[leftNeighbourID.value()].value.value() << wires[rightNeighbourID.value()].value.value();
            else if(pair.second.operation == "RSHIFT") pair.second.value = wires[leftNeighbourID.value()].value.value() >> wires[rightNeighbourID.value()].value.value();
        });
    }
}

int main(int argc, char **argv)
{
    std::unordered_map<std::string, Node> wires;
    const auto isNumber = [](const char character){ return isdigit(character); };
    
    //First, let's build the graph
    std::string instruction;
    while(std::getline(std::cin, instruction))
    {
        std::stringstream stringStream(instruction);
        std::string firstValue;
        std::getline(stringStream, firstValue, ' ');
        std::string secondValue;
        std::getline(stringStream, secondValue, ' ');
        if(secondValue == "->")
        {
            if(std::ranges::all_of(firstValue, isNumber)) 
            {
                wires[firstValue] = Node {
                    .value = static_cast<uint16_t>(std::stoi(firstValue))
                };
            }
            std::string identifier;
            std::getline(stringStream, identifier, ' ');
            wires[identifier] = Node {
                .operation = "ASSIGNMENT",
                .leftNeighbourID = firstValue
            };
        }
        else if(firstValue == "NOT")
        {
            std::string leftIdentifier = secondValue;
            std::string arrow;
            std::getline(stringStream, arrow, ' ');
            std::string rightIdentifier;
            std::getline(stringStream, rightIdentifier, ' ');
            if(std::ranges::all_of(leftIdentifier, isNumber)) 
            {
                wires[leftIdentifier] = Node {
                    .value = static_cast<uint16_t>(std::stoi(leftIdentifier))
                };
            }
            wires[rightIdentifier] = Node {
                .operation = "NOT",
                .leftNeighbourID = leftIdentifier
            };
        }
        else 
        {
            std::string leftIdentifier = firstValue;
            std::string bitwiseOperator = secondValue;
            std::string rightIdentifier;
            std::getline(stringStream, rightIdentifier, ' ');
            std::string arrow;
            std::getline(stringStream, arrow, ' ');
            std::string outputIdentifier;
            std::getline(stringStream, outputIdentifier, ' ');
            wires[outputIdentifier] = Node {
                .operation = bitwiseOperator,
                .leftNeighbourID = leftIdentifier,
                .rightNeighbourID = rightIdentifier
            };
            
            if(bitwiseOperator == "LSHIFT" || bitwiseOperator == "RSHIFT")
            {
                wires[rightIdentifier] = Node {
                    .value = static_cast<uint16_t>(std::stoi(rightIdentifier))
                };
            }
        }
    }

    //Next, let's fill all nodes with valid values
    traverseGraph(wires);
    int aValue = wires["a"].value.value();
    std::cout << "Part 1 - a: " << aValue << std::endl;

    //Change the wires
    wires[std::to_string(aValue)] = Node {
        .value = aValue
    };

    std::ranges::for_each(wires, [](auto& pair){
        if(!pair.second.operation.has_value()) return;
        pair.second.value = std::nullopt;
    });

    wires["b"] = Node {
        .value = std::nullopt,
        .operation = "ASSIGNMENT",
        .leftNeighbourID = std::to_string(aValue),
        .rightNeighbourID = std::nullopt
    };

    //Next, let's fill all nodes with valid values (again)
    traverseGraph(wires);   
    aValue = wires["a"].value.value();
    std::cout << "Part 2 - a: " << aValue << std::endl;
}