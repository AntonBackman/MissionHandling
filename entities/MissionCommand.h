//
// Created by anton on 2022-04-08.
//

#ifndef MISSIONHANDLER_MISSIONCOMMANDTEST_H
#define MISSIONHANDLER_MISSIONCOMMAND_H


#include <string>

class MissionCommand {
public:
    MissionCommand(const std::string &commandType, int executionTime, float failureProbability);

    const std::string &getCommandType() const;

    void setCommandType(const std::string &commandType);

    int getExecutionTime() const;

    void setExecutionTime(int executionTime);

    float getFailureProbability() const;

    void setFailureProbability(float failureProbability);

    static MissionCommand* parseFromCommandType(std::string commandType);

private:
        std::string commandType;
        int executionTimeSeconds;
        float failureProbability;
};


#endif //MISSIONHANDLER_MISSIONCOMMANDTEST_H
