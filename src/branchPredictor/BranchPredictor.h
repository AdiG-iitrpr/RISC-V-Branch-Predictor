#pragma once
#include "Parser.h"
#include <string>
#include <unordered_map>

class BranchPredictor {
public:

    explicit BranchPredictor(Parser &parser);
    void simulate(const std::string& traceFilePath);

private:

    Parser &parser;

    bool isBranchInstruction(const std::string &machineCode);
    std::string calculateTargetAddress(const Instruction& instruction);
    void alwaysTaken(const std::unordered_map<std::string, bool> &branchTakenMap);
    void alwaysNotTaken(const std::unordered_map<std::string, bool> &branchTakenMap);
    void oneBitPredictor(const std::unordered_map<std::string, bool> &branchTakenMap);
    void twoBitPredictor(const std::unordered_map<std::string, bool> &branchTakenMap);

};

