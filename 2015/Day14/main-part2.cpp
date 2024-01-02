#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <ranges>
#include <regex>

struct Reindeer
{
    std::string name;
    int speedInKmPerSecond{0};
    int runDuration{0};
    int restDuration{0};
    int pointsEarned{0};

    int distanceTraveled(const int seconds) const
    {
        const int sprints = seconds / (runDuration + restDuration);
        const int secondsLeft = seconds - (sprints * (runDuration + restDuration));
        return speedInKmPerSecond * runDuration * sprints + speedInKmPerSecond * (std::clamp(secondsLeft, 0, runDuration));
    }
    
};

std::vector<Reindeer> loadInput()
{
    std::string input, temp;
    std::vector<Reindeer> reindeers;
    while(std::getline(std::cin, input))
    {
        const std::regex sentenceRegex("(\\w+) can fly (\\d+) km/s for (\\d+) seconds, but then must rest for (\\d+) seconds.");
        std::smatch stringMatch;
        std::regex_search(input, stringMatch, sentenceRegex);
        
        Reindeer reindeer;
        reindeer.name = stringMatch.str(1);
        reindeer.speedInKmPerSecond = std::stoi(stringMatch.str(2));
        reindeer.runDuration = std::stoi(stringMatch.str(3));
        reindeer.restDuration = std::stoi(stringMatch.str(4));
        reindeers.push_back(reindeer);
    }
    return reindeers;
}

int main(int argc, char **argv)
{
    std::vector<Reindeer> reindeers = loadInput();
    std::ranges::for_each(std::views::iota(1, 2503), [&reindeers](const int time) {
        const auto sortByDistance = [time](const Reindeer& a, const Reindeer& b){ return a.distanceTraveled(time) < b.distanceTraveled(time); };
        const auto winnerReindeer = std::ranges::max_element(reindeers, sortByDistance);
        std::ranges::for_each(reindeers, [maxDistance = winnerReindeer->distanceTraveled(time), time](Reindeer& reindeer){
            if(reindeer.distanceTraveled(time) == maxDistance) reindeer.pointsEarned++;
        });
    });
    
    const auto sortByPoints = [](const Reindeer& a, const Reindeer& b){ return a.pointsEarned < b.pointsEarned; };
    const auto winnerReindeer = std::ranges::max_element(reindeers, sortByPoints);
    std::cout << "Points Earned by Winning Reindeer: " << winnerReindeer->pointsEarned  << std::endl;
}