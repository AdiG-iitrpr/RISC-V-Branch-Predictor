#include "../utils/FileUtils.h"
#include "../utils/NumberUtils.h"
#include "../utils/Enums.h"
#include "Instruction.h"
#include "BranchPredictor.h"
#include <iostream>
#include <vector>

BranchPredictor::BranchPredictor(Parser &parser, BranchHistoryTable &branchHistoryTable): parser(parser) , branchHistoryTable(branchHistoryTable) {

}

void BranchPredictor::simulate(const std::string& traceFilePath) {

    std::string traceContent = FileUtils::readFile(traceFilePath);

    std::vector<Instruction> instructions = parser.parse(traceContent);

    std::vector<std::pair<std::string, bool>> actualBranchOutcome;

    for (size_t i = 0; i < instructions.size(); ++i) {

        const Instruction& instruction = instructions[i];
        bool branchInstruction = isBranchInstruction(instruction.getMachineCode());

        if (branchInstruction) {

            std::string targetAddress = calculateTargetAddress(instruction);
            std::string nextAddress = i == instructions.size() - 1 ? " " : instructions[i + 1].getAddress();

            bool branchTaken = nextAddress == targetAddress;
            actualBranchOutcome.push_back(std::make_pair(instruction.getAddress(), branchTaken));

        }
    }

    bool simulation = true;
    while (simulation) {

        std::cout << "\nChoose simulation method:\n";
        std::cout << "1. Always Taken\n";
        std::cout << "2. Always Not Taken\n";
        std::cout << "3. 1-bit Dynamic Branch Predictor\n";
        std::cout << "4. 2-bit Dynamic Branch Predictor\n";
        std::cout << "5. Exit\n";

        int choice;
        std::cin >> choice;

        std::cout << "\n";

        switch (choice) {
        case 1:
            alwaysTaken(actualBranchOutcome);
            break;
        case 2:
            alwaysNotTaken(actualBranchOutcome);
            break;
        case 3:
            oneBitPredictor(actualBranchOutcome);
            break;
        case 4:
            twoBitPredictor(actualBranchOutcome);
            break;
        case 5:
            simulation = false;
            break;
        default:
            std::cerr << "Invalid choice.\n";
            break;
        }

        branchHistoryTable.clear();
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

void BranchPredictor::alwaysTaken(const std::vector<std::pair<std::string, bool>> &actualBranchOutcome) {

    int totalBranches = 0;
    int correctPredictions = 0;

    for (const auto& [address, branchOutcome] : actualBranchOutcome) {
        totalBranches++;
        if (branchOutcome)
            correctPredictions++;
    }

    double accuracy = (static_cast<double>(correctPredictions) / totalBranches) * 100.0;
    std::cout << "Branch Prediction Accuracy (Always Taken): " << accuracy << "%" << std::endl;
}

void BranchPredictor::alwaysNotTaken(const std::vector<std::pair<std::string, bool>> &actualBranchOutcome) {

    int totalBranches = 0;
    int correctPredictions = 0;

    for (const auto& [address, branchOutcome] : actualBranchOutcome) {
        totalBranches++;
        if (!branchOutcome)
            correctPredictions++;
    }

    double accuracy = (static_cast<double>(correctPredictions) / totalBranches) * 100.0;
    std::cout << "Branch Prediction Accuracy (Always Not Taken): " << accuracy << "%" << std::endl;
}

void BranchPredictor::oneBitPredictor(const std::vector<std::pair<std::string, bool>> &actualBranchOutcome) {

    int totalBranches = 0;
    int correctPredictions = 0;

    for (const auto& [address, branchOutcome] : actualBranchOutcome) {

        totalBranches++;
        if (branchHistoryTable.get(address) == BranchState::INVALID)
            branchHistoryTable.update(address, BranchState::NOT_TAKEN);

        BranchState currentState = branchHistoryTable.get(address);

        if ((branchOutcome and  currentState == BranchState::TAKEN) or (!branchOutcome and currentState == BranchState::NOT_TAKEN))
            correctPredictions++;
        else if (branchOutcome and currentState == BranchState::NOT_TAKEN)
            branchHistoryTable.update(address, BranchState::TAKEN);
        else
            branchHistoryTable.update(address, BranchState::NOT_TAKEN);
    }

    double accuracy = (static_cast<double>(correctPredictions) / totalBranches) * 100.0;
    std::cout << "Branch Prediction Accuracy (1 Bit Predictor): " << accuracy << "%" << std::endl;
}

void BranchPredictor::twoBitPredictor(const std::vector<std::pair<std::string, bool>> &actualBranchOutcome) {

    int totalBranches = 0;
    int correctPredictions = 0;

    for (const auto& [address, branchOutcome] : actualBranchOutcome) {

        totalBranches++;

        if (branchHistoryTable.get(address) == BranchState::INVALID)
            branchHistoryTable.update(address, BranchState::WEAKLY_NOT_TAKEN);

        BranchState currentState = branchHistoryTable.get(address);

        if ((currentState == BranchState::STRONGLY_NOT_TAKEN or currentState == BranchState::WEAKLY_NOT_TAKEN) and !branchOutcome)
            correctPredictions++;
        else if ((currentState == BranchState::WEAKLY_TAKEN or currentState == BranchState::STRONGLY_TAKEN) and branchOutcome)
            correctPredictions++;


        if (branchOutcome and currentState == BranchState::STRONGLY_NOT_TAKEN)
            branchHistoryTable.update(address, BranchState::WEAKLY_NOT_TAKEN);

        else if (!branchOutcome and currentState == BranchState::WEAKLY_NOT_TAKEN)
            branchHistoryTable.update(address, BranchState::STRONGLY_NOT_TAKEN);

        else if (branchOutcome and currentState == BranchState::WEAKLY_NOT_TAKEN)
            branchHistoryTable.update(address, BranchState::WEAKLY_TAKEN);

        else if (!branchOutcome and currentState == BranchState::WEAKLY_TAKEN)
            branchHistoryTable.update(address, BranchState::WEAKLY_NOT_TAKEN);

        else if (branchOutcome and currentState == BranchState::WEAKLY_TAKEN)
            branchHistoryTable.update(address, BranchState::STRONGLY_TAKEN);

        else if (!branchOutcome and currentState == BranchState::STRONGLY_TAKEN)
            branchHistoryTable.update(address, BranchState::WEAKLY_TAKEN);
    }

    double accuracy = (static_cast<double>(correctPredictions) / totalBranches) * 100.0;
    std::cout << "Branch Prediction Accuracy (2 Bit Predictor): " << accuracy << "%" << std::endl;
}
