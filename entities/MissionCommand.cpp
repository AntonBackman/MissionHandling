//
// Created by anton on 2022-04-08.
//

#include "MissionCommand.h"
#include "../helpers/StringHelpers.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <windows.h>
#include <cstdlib>
#include <future>

const std::string &MissionCommand::getCommandType() const {
    return commandType;
}

void MissionCommand::setCommandType(const std::string &commandType) {
    MissionCommand::commandType = commandType;
}

int MissionCommand::getExecutionTime() const {
    return executionTimeSeconds;
}

void MissionCommand::setExecutionTime(int executionTime) {
    MissionCommand::executionTimeSeconds = executionTime;
}

float MissionCommand::getFailureProbability() const {
    return failureProbability;
}

void MissionCommand::setFailureProbability(float failureProbability) {
    MissionCommand::failureProbability = failureProbability;
}

Status MissionCommand::getStatus() const {
    return status;
}

void MissionCommand::setStatus(Status status) {
    MissionCommand::status = status;
}

const std::string &MissionCommand::getReplaceableByCommandType() const {
    return replaceableByCommandType;
}

void MissionCommand::setReplaceableByCommandType(const std::string &replaceableByCommandType) {
    MissionCommand::replaceableByCommandType = replaceableByCommandType;
}


MissionCommand* MissionCommand::parseFromCommandType(const std::string& commandType) {
    if(commandType == "DriveForward") {
        return new MissionCommand("DriveForward", 5, 0.05, "DriveForward");
    } else if (commandType == "Reverse") {
        return new MissionCommand("Reverse", 5, 0.07, "Reverse");
    } else if (commandType == "Dump") {
        return new MissionCommand("Dump", 10, 0.01, "None");
    } else if (commandType == "FlashHighBeam") {
        return new MissionCommand("FlashHighBeam", 1, 0.005, "Any");
    } else {
        throw std::runtime_error("Could not parse to MissionCommand: " + commandType);
    }
}

MissionCommand::MissionCommand(const std::string &commandType, int executionTime, float failureProbability, const std::string &replaceableByCommandType)
        : commandType(commandType), executionTimeSeconds(executionTime), failureProbability(failureProbability), replaceableByCommandType(replaceableByCommandType) {
    MissionCommand::status = PENDING;
}

std::vector<MissionCommand *> MissionCommand::getMissionCommands(const std::vector<std::string>& commands) {
    std::vector<MissionCommand*> missionCommands = MissionCommand::parseFromCommandTypes(commands);
    MissionCommand::validateMission(missionCommands);
    return missionCommands;
}

std::vector<MissionCommand *> MissionCommand::parseFromCommandTypes(const std::vector<std::string>& commandTypes) {
    std::vector<MissionCommand*> missionCommands;
    missionCommands.reserve(commandTypes.size());
    for (auto &command : commandTypes) {
        missionCommands.push_back(MissionCommand::parseFromCommandType(command));
    }
    return missionCommands;
}

void MissionCommand::validateMission(const std::vector<MissionCommand *>& missionCommands) {
    validateSize(missionCommands);
    validateDump(missionCommands);
}

void MissionCommand::validateSize(const std::vector<MissionCommand *> &missionCommands) {
    if (missionCommands.size() > 5) {
        throw std::runtime_error("Validation error: There are more than 5 commands");
    }
}

void MissionCommand::validateDump(const std::vector<MissionCommand *> &missionCommands) {
    MissionCommand* previousCommand = missionCommands.front();
    for (auto* missionCommand : missionCommands) {
        if (missionCommand->getCommandType() == "Dump" && previousCommand->getCommandType() != "Reverse") {
            throw std::runtime_error("Validation error: Dump is not done after a Reverse command");
        }
        previousCommand = missionCommand;
    }
}

void MissionCommand::runMissionCommands(const std::vector<MissionCommand *> &missionCommands, std::atomic_bool &cancellation) {
    srand (static_cast <unsigned> (time(nullptr)));
    for (auto* missionCommand : missionCommands) {
        missionCommand->setStatus(EXECUTING);
        executeMissionCommand(missionCommand, cancellation);
        if (missionCommand->getStatus() == ABORTED) {
            return;
        }
        missionCommand->setStatus(DONE);
    }
}

void MissionCommand::executeMissionCommand(MissionCommand *missionCommand, std::atomic_bool &cancellation) {
    // Actual MissionCommand execution
    for (int i = 0; i <= missionCommand->getExecutionTime(); i++) {
        std::cout << missionCommand->getCommandType() + " executing (" << i << "s)\n";
        if (cancellation) {
            std::cout << "MissionCommands cancelled!\n";
            missionCommand->setStatus(ABORTED);
            return;
        }
        Sleep(1000);
    }

    // Check if MissionCommand failed
    float randomFloat = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    if (randomFloat < missionCommand->getFailureProbability()) {
        missionCommand->setStatus(FAILED);
        std::cout << "Failed MissionCommand: " + missionCommand->getCommandType() << "\n";
        throw std::runtime_error("Failed MissionCommand: " + missionCommand->getCommandType());
    }
}

void MissionCommand::report(const std::vector<MissionCommand *> &missionCommands) {
    std::cout << "\nMission report:\n";
    for (auto* missionCommand : missionCommands) {
        std::cout << "MissionCommand: " << missionCommand->getCommandType() << ", Status: " << getStatusAsString(missionCommand) << "\n";
    }
}

std::string MissionCommand::getStatusAsString(const MissionCommand *missionCommand) {
    std::string status;
    switch (missionCommand->getStatus()) {
        case PENDING:
            status = "Pending";
            break;
        case EXECUTING:
            status = "Executing";
            break;
        case FAILED:
            status = "Failed";
            break;
        case DONE:
            status = "Done";
            break;
        case ABORTED:
            status = "Aborted";
            break;
    }
    return status;
}

std::vector<MissionCommand*> MissionCommand::getMissionCommandsFromTerminal() {
    std::vector<std::string> splitInputCommands = getCommands();

    std::vector<MissionCommand*> missionCommands;
    try {
        missionCommands = MissionCommand::getMissionCommands(splitInputCommands);
    } catch (const std::runtime_error& e) {
        std::cout << "Mission rejected: \n" << e.what();
    }
    return missionCommands;
}

MissionCommand* MissionCommand::getFirstAbortedMissionCommand(std::vector<MissionCommand*> missionCommands) {
    for (auto* missionCommand : missionCommands) {
        if (missionCommand->getStatus() == ABORTED) {
            return missionCommand;
        }
    }
}