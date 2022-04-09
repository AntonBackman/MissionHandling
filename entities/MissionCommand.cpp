//
// Created by anton on 2022-04-08.
//

#include "MissionCommand.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <windows.h>

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


MissionCommand* MissionCommand::parseFromCommandType(const std::string& commandType) {
    if(commandType == "DriveForward") {
        return new MissionCommand("DriveForward", 5, 0.05);
    } else if (commandType == "Reverse") {
        return new MissionCommand("Reverse", 5, 0.07);
    } else if (commandType == "Dump") {
        return new MissionCommand("Dump", 10, 0.01);
    } else if (commandType == "FlashHighBeam") {
        return new MissionCommand("FlashHighBeam", 1, 0.005);
    } else {
        throw std::runtime_error("Could not parse to MissionCommand: " + commandType);
    }
}

MissionCommand::MissionCommand(const std::string &commandType, int executionTime, float failureProbability)
        : commandType(commandType), executionTimeSeconds(executionTime), failureProbability(failureProbability) {
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
    std::cout << "Mission accepted!\n";
}

void MissionCommand::validateSize(const std::vector<MissionCommand *> &missionCommands) {
    if (missionCommands.size() > 5) {
        throw std::runtime_error("Validation error: There are more than 5 commands");
    }
}

void MissionCommand::validateDump(const std::vector<MissionCommand *> &missionCommands) {
    MissionCommand* previousCommand;
    for (auto* missionCommand : missionCommands) {
        if (missionCommand->getCommandType() == "Dump" && previousCommand->getCommandType() != "Reverse") {
            throw std::runtime_error("Validation error: Dump is not done after a Reverse command");
        }
        previousCommand = missionCommand;
    }
}

void MissionCommand::runMissionCommands(const std::vector<MissionCommand *> &missionCommands) {
    for (auto* missionCommand : missionCommands) {
        missionCommand->setStatus(EXECUTING);
        executeMissionCommand(missionCommand);
        missionCommand->setStatus(DONE);
    }
}

void MissionCommand::executeMissionCommand(MissionCommand *missionCommand) {
    // Actual MissionCommand execution
    for (int i = 0; i <= missionCommand->getExecutionTime(); i++) {
        std::cout << missionCommand->getCommandType() + " executing (" << i << "s)\n";
        Sleep(1000);
    }

    // Check if MissionCommand failed
    srand((unsigned)time(nullptr ) );
    float randomFloat = (float) rand()/RAND_MAX;
    if (randomFloat < missionCommand->getFailureProbability()) {
        missionCommand->setStatus(FAILED);
        throw std::runtime_error("Failed MissionCommand: " + missionCommand->getCommandType());
    }
}
