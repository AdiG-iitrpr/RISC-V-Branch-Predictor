#include "FileUtils.h"

#include <iostream>

#define MAX_LINES 1000000

std::string FileUtils::readFile(const std::string& filePath) {

    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file: " + filePath);
    }

    std::stringstream buffer;
    std::string line;
    size_t lineCount = 0;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            buffer << line << '\n';
            ++lineCount;
        }

        if (lineCount >= MAX_LINES)
            break;
    }

    return buffer.str();
}
