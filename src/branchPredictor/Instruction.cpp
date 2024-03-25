#include "Instruction.h"

Instruction::Instruction(const std::string& address, const std::string& machineCode)
    : address(address), machineCode(machineCode) {}

const std::string& Instruction::getAddress() const {
    return address;
}

const std::string& Instruction::getMachineCode() const {
    return machineCode;
}
