//
// Created by anton on 2022-04-08.
//

#ifndef MISSIONHANDLER_MISSIONCOMMANDTEST_H
#define MISSIONHANDLER_MISSIONCOMMAND_H


#include <string>
#include <vector>
#include <future>

enum Status {PENDING, EXECUTING, FAILED, DONE, ABORTED};

class MissionCommand {
public:
    MissionCommand(const std::string &commandType, int executionTime, float failureProbability, const std::string &replaceableByCommandType);

    const std::string &getCommandType() const;

    void setCommandType(const std::string &commandType);

    int getExecutionTime() const;

    void setExecutionTime(int executionTime);

    float getFailureProbability() const;

    void setFailureProbability(float failureProbability);

    Status getStatus() const;

    void setStatus(Status status);

    const std::string &getReplaceableByCommandType() const;

    void setReplaceableByCommandType(const std::string &replaceableByCommandType);

    static MissionCommand* parseFromCommandType(const std::string& commandType);

    static std::vector<MissionCommand*> getMissionCommands(const std::vector<std::string>& commands);

    static std::vector<MissionCommand*> parseFromCommandTypes(const std::vector<std::string>& commandTypes);

    static void validateMission(const std::vector<MissionCommand *>& missionCommands);

    static void runMissionCommands(const std::vector<MissionCommand *> &missionCommands, std::atomic_bool &cancellation);

    static void report(const std::vector<MissionCommand *> &missionCommands);

    static std::vector<MissionCommand*> getMissionCommandsFromTerminal();

    static MissionCommand* getFirstAbortedMissionCommand(std::vector<MissionCommand*> missionCommands);

private:
        std::string commandType;
        std::string replaceableByCommandType;

private:
    int executionTimeSeconds;
        float failureProbability;
        Status status;

    static void validateDump(const std::vector<MissionCommand *> &missionCommands);

    static void validateSize(const std::vector<MissionCommand *> &missionCommands);

    static void executeMissionCommand(MissionCommand *missionCommand, std::atomic_bool &cancellation);

    static std::string getStatusAsString(const MissionCommand *missionCommand);
};


#endif //MISSIONHANDLER_MISSIONCOMMANDTEST_H
