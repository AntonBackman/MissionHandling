#include <iostream>
#include "entities/MissionCommand.h"

int main() {
    auto missionCommands = MissionCommand::getMissionCommandsFromTerminal();

    if (!missionCommands.empty()) {
        try {
            std::cout << "\nMission progress:\n";
            MissionCommand::runMissionCommands(missionCommands);
            std::cout << "Mission complete!\n";
        } catch (const std::runtime_error& e) {
            std::cout << "Could not finish mission!\n" << e.what();
        }

        MissionCommand::report(missionCommands);
    }
    return 0;
}
