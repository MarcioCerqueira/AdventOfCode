#include <iostream>
#include <algorithm>

struct Reindeer
{
    std::string name;
    int speedInKmPerSecond{0};
    int runDuration{0};
    int restDuration{0};

    int distanceTraveled(const int seconds) const
    {
        const int sprints = seconds / (runDuration + restDuration);
        const int secondsLeft = seconds - (sprints * (runDuration + restDuration));
        return speedInKmPerSecond * runDuration * sprints + speedInKmPerSecond * (std::clamp(secondsLeft, 0, runDuration));
    }
    
};

int main(int argc, char **argv)
{
    const Reindeer Comet{.name = "Comet", .speedInKmPerSecond = 14, .runDuration = 10, .restDuration = 127};
    const Reindeer Dancer{.name = "Dancer", .speedInKmPerSecond = 16, .runDuration = 11, .restDuration = 162};
    
    int timeTraveled{0};
    std::cin >> timeTraveled;

    std::cout << "Distance Traveled by Winning Reindeer: " << std::max(Comet.distanceTraveled(timeTraveled), Dancer.distanceTraveled(timeTraveled));
}