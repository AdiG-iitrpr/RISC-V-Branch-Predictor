#include "NumberUtils.h"

std::bitset<32> NumberUtils::hexadecimalToBitset(const std::string& hexString) {

	std::stringstream ss;
	ss << std::hex << hexString;
	unsigned int intValue;
	ss >> intValue;

	return std::bitset<32>(intValue);
}

std::string NumberUtils::addIntegerToHexadecimal(const std::string& hexString, int value) {

	std::stringstream ss;
	ss << std::hex << hexString;
	unsigned int integerValue;
	ss >> integerValue;

	integerValue += value;

	std::stringstream resultStream;
	resultStream << "0x" << std::hex << std::setw(8) << std::setfill('0') << integerValue;
	return resultStream.str();
}