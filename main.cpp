#include <iostream>
#include "entities/MissionCommand.h"

int main() {
    auto* driveForward = MissionCommand::parseFromCommandType("DriveForward");

    auto* blarg = MissionCommand::parseFromCommandType("blarg");
    return 0;
}
