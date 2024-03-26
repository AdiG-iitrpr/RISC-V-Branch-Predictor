#include "BranchHistoryTable.h"

BranchHistoryTable::BranchHistoryTable() {}

void BranchHistoryTable::update(const std::string& address, BranchState state) {
    history_table[address] = state;
}

BranchState BranchHistoryTable::get(const std::string& address) const {
    auto it = history_table.find(address);
    if (it != history_table.end()) {
        return it->second;
    }
    return BranchState::INVALID;
}

void BranchHistoryTable::clear() {
    history_table.clear();
}
