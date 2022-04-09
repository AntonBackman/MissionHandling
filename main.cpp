#include <iostream>
#include "entities/MissionCommand.h"
#include "helpers/StringHelpers.h"
#include <vector>
#include <sstream>

using namespace std;

int main() {
    stringstream inputCommands("DriveForward, Reverse");
    vector<string> splittedCommands = splitAndTrim(inputCommands, ',');

    vector<MissionCommand*> missionCommands = MissionCommand::parseFromCommandTypes(splittedCommands);
    return 0;
}
