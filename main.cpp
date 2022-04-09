#include <iostream>
#include "entities/MissionCommand.h"
#include "helpers/StringHelpers.h"
#include <vector>
#include <sstream>

using namespace std;

int main() {
    string input;
    getline(cin, input);
    stringstream inputCommands(input);

    vector<string> splitInputCommands = splitAndTrim(inputCommands, ',');

    vector<MissionCommand*> missionCommands = MissionCommand::parseFromCommandTypes(splitInputCommands);
    return 0;
}
