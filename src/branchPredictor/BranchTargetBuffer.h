#pragma once

#include <unordered_map>
#include <string>
#include "../utils/Enums.h"

class BranchTargetBuffer {
public:
    BranchTargetBuffer();

    void update(const std::string& branchAddress, const std::string& targetAddress, BranchState state);
    std::pair<std::string, BranchState> get(const std::string& branchAddress) const;
    void printTargetBuffer() const;
    void clear();

private:
    std::unordered_map<std::string, std::pair<std::string, BranchState>> buffer;
};
