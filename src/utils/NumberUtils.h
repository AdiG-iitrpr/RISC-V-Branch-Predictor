#pragma once

#include <bitset>
#include <string>
#include <sstream>
#include <iomanip>

class NumberUtils {
public:
    static std::bitset<32> hexadecimalToBitset(const std::string& hexString);
    static std::string addIntegerToHexadecimal(const std::string& hexString, int value);
};
