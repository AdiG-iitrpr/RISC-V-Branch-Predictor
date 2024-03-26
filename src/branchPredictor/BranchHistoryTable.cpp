#include "BranchHistoryTable.h"

BranchHistoryTable::BranchHistoryTable() {}

void BranchHistoryTable::update(const std::string& address, bool taken) {
    history_table[address] = taken;
}

int BranchHistoryTable::get(const std::string& address) const {
    auto it = history_table.find(address);
    if (it != history_table.end()) {
        return it->second == true ? 1 : 0 ;
    }
    return -1;
}

void BranchHistoryTable::clear() {
    history_table.clear();
}
