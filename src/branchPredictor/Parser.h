#pragma once

#include "Instruction.h"
#include <vector>
#include <string>

class Parser {
public:
    std::vector<Instruction> parse(const std::string& input);

private:

    bool isWhitespace(char c);
    bool isDelimiter(char c);
    bool isComment(char c);
};