#include <iostream>
#include "entities/MissionCommand.h"
#include "helpers/StringHelpers.h"
#include <vector>
#include <sstream>

std::vector<std::string> getCommands();

int main() {
    std::vector<std::string> splitInputCommands = getCommands();

    std::vector<MissionCommand*> missionCommands = MissionCommand::getMissionCommands(splitInputCommands);

    std::cout << "Mission progress:\n";
    MissionCommand::runMissionCommands(missionCommands);

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
