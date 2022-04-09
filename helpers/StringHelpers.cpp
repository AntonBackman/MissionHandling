//
// Created by anton on 2022-04-09.
//

#include "StringHelpers.h"
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <vector>
#include <sstream>

std::vector<std::string> splitAndTrim(std::stringstream& input, char delimiter) {
    std::string segment;
    std::vector<std::string> seglist;

    while(std::getline(input, segment, delimiter))
    {
        seglist.push_back(trim(segment));
    }
    return seglist;
}

// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}