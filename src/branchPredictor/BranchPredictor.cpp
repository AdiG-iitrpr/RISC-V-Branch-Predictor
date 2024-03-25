#include "../utils/FileUtils.h"
#include "../utils/NumberUtils.h"
#include "Instruction.h"
#include "BranchPredictor.h"
#include <iostream>
#include <vector>

BranchPredictor::BranchPredictor(Parser &parser): parser(parser) {

}

void BranchPredictor::simulate(const std::string& traceFilePath) {

    std::string traceContent = FileUtils::readFile(traceFilePath);

    std::vector<Instruction> instructions = parser.parse(traceContent);

    std::unordered_map<std::string, bool> branchTakenMap;

    for (size_t i = 0; i < instructions.size(); ++i) {

        const Instruction& instruction = instructions[i];
        bool branchInstruction = isBranchInstruction(instruction.getMachineCode());

        if (branchInstruction) {

            std::string targetAddress = calculateTargetAddress(instruction);
            std::string nextAddress = i == instructions.size() - 1 ? " " : instructions[i + 1].getAddress();

            bool branchTaken = nextAddress == targetAddress;
            branchTakenMap[instruction.getAddress()] = branchTaken;

        }
    }

    bool simulation = true;
    while (simulation) {

        std::cout << "Choose simulation method:\n";
        std::cout << "1. Always Taken\n";
        std::cout << "2. Always Not Taken\n";
        std::cout << "3. 1-bit Dynamic Branch Predictor\n";
        std::cout << "4. 2-bit Dynamic Branch Predictor\n";
        std::cout << "5. Exit\n";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            alwaysTaken(branchTakenMap);
            break;
        case 2:
            alwaysNotTaken(branchTakenMap);
            break;
        case 3:
            oneBitPredictor(branchTakenMap);
            break;
        case 4:
            twoBitPredictor(branchTakenMap);
            break;
        case 5:
            simulation = false;
            break;
        default:
            std::cerr << "Invalid choice.\n";
            break;
        }
    }
}

bool BranchPredictor::isBranchInstruction(const std::string &machineCode) {

    std::bitset<32> binaryMachineCode = NumberUtils::hexadecimalToBitset(machineCode);
    std::bitset<7> opcodeBits(binaryMachineCode.to_string().substr(25, 7));
    int opcode = static_cast<int>(opcodeBits.to_ulong());

    return opcode == 99;
}

std::string BranchPredictor::calculateTargetAddress(const Instruction& instruction) {

    std::string currentAddress = instruction.getAddress();
    std::string machineCode = instruction.getMachineCode();

    std::bitset<32> binaryMachineCode = NumberUtils::hexadecimalToBitset(machineCode);
    std::string binaryMachineCodeString = binaryMachineCode.to_string();

    std::string offsetBitsString = binaryMachineCodeString[24] + binaryMachineCodeString.substr(1, 6) + binaryMachineCodeString.substr(20, 4) + "0";

    std::bitset<12> offsetBits(offsetBitsString);
    int offset = static_cast<int>(offsetBits.to_ulong());

    // if sign bit is 1

    if (binaryMachineCodeString[0] == '1')
        offset = -4096 - (~(offset - 1));

    std::string targetAddress = NumberUtils::addIntegerToHexadecimal(currentAddress, offset);

    return targetAddress;
}

void BranchPredictor::alwaysTaken(const std::unordered_map<std::string, bool> &branchTakenMap) {

    int totalBranches = 0;
    int correctPredictions = 0;

    for (const auto& pair : branchTakenMap) {
        totalBranches++;
        if (pair.second == true) {
            correctPredictions++;
        }
    }

    double accuracy = (static_cast<double>(correctPredictions) / totalBranches) * 100.0;
    std::cout << "Branch Prediction Accuracy (Always Taken): " << accuracy << "%" << std::endl;
}

void BranchPredictor::alwaysNotTaken(const std::unordered_map<std::string, bool> &branchTakenMap) {

    int totalBranches = 0;
    int correctPredictions = 0;

    for (const auto& pair : branchTakenMap) {
        totalBranches++;
        if (pair.second != true) {
            correctPredictions++;
        }
    }

    double accuracy = (static_cast<double>(correctPredictions) / totalBranches) * 100.0;
    std::cout << "Branch Prediction Accuracy (Always Not Taken): " << accuracy << "%" << std::endl;
}

void BranchPredictor::oneBitPredictor(const std::unordered_map<std::string, bool> &branchTakenMap) {

    int totalBranches = 0;
    int correctPredictions = 0;

    bool predicted = true;

    for (const auto& pair : branchTakenMap) {
        totalBranches++;
        if (pair.second != predicted) {
            correctPredictions++;
        } else
            predicted = !predicted;
    }

    double accuracy = (static_cast<double>(correctPredictions) / totalBranches) * 100.0;
    std::cout << "Branch Prediction Accuracy (1 Bit Predictor): " << accuracy << "%" << std::endl;
}

void BranchPredictor::twoBitPredictor(const std::unordered_map<std::string, bool> &branchTakenMap) {

}
