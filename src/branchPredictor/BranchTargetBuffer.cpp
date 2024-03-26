#include "BranchTargetBuffer.h"
#include <iostream>

BranchTargetBuffer::BranchTargetBuffer() {}

void BranchTargetBuffer::update(const std::string& branchAddress, const std::string& targetAddress, BranchState state) {
    buffer[branchAddress] = std::make_pair(targetAddress, state);
}

std::pair<std::string, BranchState> BranchTargetBuffer::get(const std::string& branchAddress) const {
    auto it = buffer.find(branchAddress);
    if (it != buffer.end()) {
        return it->second;
    }

    return std::make_pair("", BranchState::INVALID);
}

void BranchTargetBuffer::printTargetBuffer() const {
    std::cout << "Branch Target Buffer:\n";
    for (const auto& [branchAddress, entry] : buffer) {
        const auto& [targetAddress, state] = entry;
        std::cout << branchAddress << " " << targetAddress;
        switch (state) {
        case BranchState::STRONGLY_TAKEN:
            std::cout << " ST\n";
            break;
        case BranchState::WEAKLY_TAKEN:
            std::cout << " WT\n";
            break;
        case BranchState::STRONGLY_NOT_TAKEN:
            std::cout << " SNT\n";
            break;
        case BranchState::WEAKLY_NOT_TAKEN:
            std::cout << " WNT\n";
            break;
        case BranchState::TAKEN:
            std::cout << " T\n";
            break;
        case BranchState::NOT_TAKEN:
            std::cout << " NT\n";
            break;
        default:
            std::cout << " Invalid\n";
        }
    }
}

void BranchTargetBuffer::clear() {
    buffer.clear();
}

