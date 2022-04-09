//
// Created by anton on 2022-04-08.
//

#include "MissionCommand.h"
#include <stdexcept>

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

MissionCommand* MissionCommand::parseFromCommandType(std::string commandType) {
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
        : commandType(commandType), executionTimeSeconds(executionTime), failureProbability(failureProbability) {}