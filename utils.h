#pragma once
#include <string>
#include <algorithm>

// Converts a string to lowercase for case-insensitive label matching
inline std::string toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}
