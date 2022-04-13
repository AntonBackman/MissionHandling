//
// Created by anton on 2022-04-09.
//

#ifndef MISSIONHANDLER_STRINGHELPERS_H
#define MISSIONHANDLER_STRINGHELPERS_H

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <vector>
#include <sstream>


std::vector<std::string> splitAndTrim(std::stringstream& input, char delimiter);
static inline std::string &trim(std::string &s);
std::vector<std::string> getCommands();

#endif //MISSIONHANDLER_STRINGHELPERS_H
