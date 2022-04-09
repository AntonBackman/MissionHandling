#include <iostream>
#include "entities/MissionCommand.h"
#include "helpers/StringHelpers.h"
#include <vector>
#include <sstream>

std::vector<std::string> getCommands();

int main() {
    std::vector<std::string> splitInputCommands = getCommands();

    std::vector<MissionCommand*> missionCommands = MissionCommand::getMissionCommands(splitInputCommands);

    try {
        std::cout << "\nMission progress:\n";
        MissionCommand::runMissionCommands(missionCommands);
        std::cout << "Mission complete!\n";
    } catch (const std::runtime_error& e) {
        std::cout << "Could not finish mission!\n";
    }

    MissionCommand::report(missionCommands);

    return 0;
}

std::vector<std::string> getCommands() {
    std::string input;
    getline(std::cin, input);
    std::stringstream commands(input);
    std::vector<std::string> splitCommands = splitAndTrim(commands, ',');
    return splitCommands;
}
