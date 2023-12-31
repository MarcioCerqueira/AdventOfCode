#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <ranges>

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
        Reindeer reindeer;
        std::stringstream stringStream(input);
        std::getline(stringStream, reindeer.name, ' ');
        std::getline(stringStream, temp, ' ');
        std::getline(stringStream, temp, ' ');
        std::getline(stringStream, temp, ' ');
        reindeer.speedInKmPerSecond = std::stoi(temp);
        std::getline(stringStream, temp, ' ');
        std::getline(stringStream, temp, ' ');
        std::getline(stringStream, temp, ' ');
        reindeer.runDuration = std::stoi(temp);
        std::getline(stringStream, temp, ' ');
        std::getline(stringStream, temp, ' ');
        std::getline(stringStream, temp, ' ');
        std::getline(stringStream, temp, ' ');
        std::getline(stringStream, temp, ' ');
        std::getline(stringStream, temp, ' ');
        std::getline(stringStream, temp, ' ');
        reindeer.restDuration = std::stoi(temp);
        std::getline(stringStream, temp, ' ');
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