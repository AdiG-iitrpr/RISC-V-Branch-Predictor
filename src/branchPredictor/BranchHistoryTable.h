#pragma once

#include <unordered_map>
#include <string>

class BranchHistoryTable {
public:

    BranchHistoryTable();
    void update(const std::string& address, bool taken);
    int get(const std::string& address) const;
    void clear();

private:
    std::unordered_map<std::string, bool> history_table;
};

