#pragma once
#include "Parser.h"
#include <string>

class BranchPredictor {
public:

    explicit BranchPredictor(Parser &parser);
    void simulate(const std::string& traceFilePath);

private:

    Parser &parser;

    void alwaysTaken();
    void alwaysNotTaken();
    void oneBitPredictor();
    void twoBitPredictor();

};

