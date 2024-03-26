#include "BranchTargetBuffer.h"
#include <iostream>
#include <iomanip>

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

    std::cout << std::setw(15) << std::left << "Branch Address" << "| ";
    std::cout << std::setw(15) << std::left << "Target Address" << "| ";
    std::cout << std::setw(10) << std::left << "State" << "|\n";
    std::cout << std::string(45, '-') << "\n";

    for (const auto& [branchAddress, entry] : buffer) {
        const auto& [targetAddress, state] = entry;
        std::cout << std::setw(15) << std::left << branchAddress << "| ";
        std::cout << std::setw(15) << std::left << targetAddress << "| ";

        switch (state) {
        case BranchState::STRONGLY_TAKEN:
            std::cout << std::setw(10) << std::left << "ST";
            break;
        case BranchState::WEAKLY_TAKEN:
            std::cout << std::setw(10) << std::left << "WT";
            break;
        case BranchState::STRONGLY_NOT_TAKEN:
            std::cout << std::setw(10) << std::left << "SNT";
            break;
        case BranchState::WEAKLY_NOT_TAKEN:
            std::cout << std::setw(10) << std::left << "WNT";
            break;
        case BranchState::TAKEN:
            std::cout << std::setw(10) << std::left << "T";
            break;
        case BranchState::NOT_TAKEN:
            std::cout << std::setw(10) << std::left << "NT";
            break;
        default:
            std::cout << std::setw(10) << std::left << "Invalid";
        }

        std::cout << "|\n";
    }

    std::cout << std::string(45, '-') << "\n";
}



void BranchTargetBuffer::clear() {
    buffer.clear();
}

