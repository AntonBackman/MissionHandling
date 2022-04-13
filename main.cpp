#include <iostream>
#include "entities/MissionCommand.h"
#include "helpers/StringHelpers.h"
#include <vector>

int main() {

    std::vector<std::string> splitInputCommands = getCommands();

    std::vector<MissionCommand*> missionCommands;
    bool shouldRunMissionCommands = false;
    try {
        missionCommands = MissionCommand::getMissionCommands(splitInputCommands);
        shouldRunMissionCommands = true;
    } catch (const std::runtime_error& e) {
        std::cout << "Mission rejected: \n";
        std::cerr << e.what();
    }

    if (shouldRunMissionCommands) {
        try {
            std::cout << "\nMission progress:\n";
            MissionCommand::runMissionCommands(missionCommands);
            std::cout << "Mission complete!\n";
        } catch (const std::runtime_error& e) {
            std::cout << "Could not finish mission!\n";
            std::cerr << e.what();
        }

        MissionCommand::report(missionCommands);
    }

    return 0;
}
