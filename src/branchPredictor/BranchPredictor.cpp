#include "../utils/FileUtils.h"
#include "Instruction.h"
#include "BranchPredictor.h"
#include <iostream>
#include <vector>

BranchPredictor::BranchPredictor(Parser &parser): parser(parser) {

}

void BranchPredictor::simulate(const std::string& traceFilePath) {

    std::string traceContent = FileUtils::readFile(traceFilePath);

    std::vector<Instruction> instructions = parser.parse(traceContent);

    std::cout << "Choose simulation method:\n";
    std::cout << "1. Always Taken\n";
    std::cout << "2. Always Not Taken\n";
    std::cout << "3. 1-bit Dynamic Branch Predictor\n";
    std::cout << "4. 2-bit Dynamic Branch Predictor\n";

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
        alwaysTaken();
        break;
    case 2:
        alwaysNotTaken();
        break;
    case 3:
        oneBitPredictor();
        break;
    case 4:
        twoBitPredictor();
        break;
    default:
        std::cerr << "Invalid choice.\n";
        break;
    }
}

void BranchPredictor::alwaysTaken() {

}

void BranchPredictor::alwaysNotTaken() {

}

void BranchPredictor::oneBitPredictor() {

}

void BranchPredictor::twoBitPredictor() {

}
