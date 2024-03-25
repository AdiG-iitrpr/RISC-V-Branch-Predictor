#pragma once
#include <string>

class Instruction {
public:

    Instruction(const std::string& address, const std::string& machineCode);

    const std::string& getAddress() const;
    const std::string& getMachineCode() const;

private:

    std::string address;
    std::string machineCode;
};
