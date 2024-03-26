#pragma once

#include "../utils/Enums.h"
#include <unordered_map>
#include <string>

class BranchHistoryTable {
public:

    BranchHistoryTable();
    void update(const std::string& address, BranchState state);
    BranchState get(const std::string& address) const;
    void clear();

private:
    std::unordered_map<std::string, BranchState> history_table;
};

