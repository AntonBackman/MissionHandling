#include <iostream>
#include <chrono>
#include <future>
#include "entities/MissionCommand.h"
#include "helpers/StringHelpers.h"
#include <windows.h>

void executeMission(const std::vector<MissionCommand *> &missionCommands);

bool isAbortedMissionReplaceable(const MissionCommand *firstAbortedMissionCommand, MissionCommand * &missionCommand);

int main() {
    MissionCommand* firstAbortedMissionCommand = NULL;
    bool runLoop = true;
    while(runLoop) {
        if (firstAbortedMissionCommand != NULL) {
            std::cout << "Last, aborted, command: " << firstAbortedMissionCommand->getCommandType() <<
            ". Can only be replaced by: " << firstAbortedMissionCommand->getReplaceableByCommandType() << "\n";
        }
        auto missionCommands = MissionCommand::getMissionCommandsFromTerminal();

        if (!missionCommands.empty() && (firstAbortedMissionCommand == NULL || isAbortedMissionReplaceable(firstAbortedMissionCommand, missionCommands.front()))) {
            std::cout << "Mission accepted!\n";
            executeMission(missionCommands);
            firstAbortedMissionCommand = MissionCommand::getFirstAbortedMissionCommand(missionCommands);
        }

        if (firstAbortedMissionCommand == NULL) {
            runLoop = false;
        }
    }
    return 0;
}

bool isAbortedMissionReplaceable(const MissionCommand *abortedMissionCommand, MissionCommand * &missionCommand) {
    if (abortedMissionCommand->getReplaceableByCommandType() == "Any") {
        return true;
    }
    if (abortedMissionCommand->getReplaceableByCommandType() == "None") {
        return false;
    }
    return abortedMissionCommand->getReplaceableByCommandType() == missionCommand->getCommandType();
}

void executeMission(const std::vector<MissionCommand *> &missionCommands) {
    try {
        std::cout << "\nMission progress:\n";
        std::atomic_bool cancellation_token;
        auto future = std::async(std::launch::async, MissionCommand::runMissionCommands, missionCommands, std::ref(cancellation_token));
        auto futureCancellation = std::async(std::launch::async, setCancellation, std::ref(cancellation_token));
        future.get();
        if (cancellation_token) {
            std::cout << "Mission cancelled!\n";
        } else {
            std::cout << "Mission complete!\n";
        }
    } catch (const std::runtime_error& e) {
        std::cout << "Could not finish mission!\n" << e.what();
    }
    MissionCommand::report(missionCommands);
}
