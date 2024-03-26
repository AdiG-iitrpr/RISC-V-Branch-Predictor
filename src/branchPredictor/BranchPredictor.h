#pragma once

#include "Parser.h"
#include "BranchHistoryTable.h"
#include "BranchTargetBuffer.h"

#include <string>
#include <unordered_map>

class BranchPredictor {
public:

    explicit BranchPredictor(Parser &parser, BranchHistoryTable &branchHistoryTable, BranchTargetBuffer &branchTargetBuffer);
    void simulate(const std::string& traceFilePath);

private:

    Parser &parser;
    BranchHistoryTable &branchHistoryTable;
    BranchTargetBuffer &branchTargetBuffer;

    bool isBranchInstruction(const std::string &machineCode);
    std::string calculateTargetAddress(const Instruction& instruction);
    void alwaysTaken(const  std::vector<std::pair<std::pair<std::string, std::string>, bool>> &actualBranchOutcome);
    void alwaysNotTaken(const  std::vector<std::pair<std::pair<std::string, std::string>, bool>>&actualBranchOutcome);
    void oneBitPredictor(const  std::vector<std::pair<std::pair<std::string, std::string>, bool>> &actualBranchOutcome);
    void twoBitPredictor(const  std::vector<std::pair<std::pair<std::string, std::string>, bool>> &actualBranchOutcome);

};

