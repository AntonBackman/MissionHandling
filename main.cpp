#include <iostream>
#include <chrono>
#include <future>
#include "entities/MissionCommand.h"
#include <windows.h>

int main() {
    srand (static_cast <unsigned> (time(nullptr)));
    auto missionCommands = MissionCommand::getMissionCommandsFromTerminal();

    if (!missionCommands.empty()) {
        try {
            std::cout << "\nMission progress:\n";
            std::atomic_bool cancellation_token;
            auto future = std::async(std::launch::async, MissionCommand::runMissionCommands, missionCommands, std::ref(cancellation_token));
            auto newMissionCommands = MissionCommand::getMissionCommandsFromTerminal();
            cancellation_token = true;
            future.get();
            std::cout << "Mission complete!\n";
        } catch (const std::runtime_error& e) {
            std::cout << "Could not finish mission!\n" << e.what();
        }

        MissionCommand::report(missionCommands);
    }
    return 0;
}
