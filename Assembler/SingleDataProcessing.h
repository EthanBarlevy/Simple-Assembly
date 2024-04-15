#pragma once
#include "Command.h"

class SingleDataProcessing : public Command
{
public:
	std::bitset<8>* GetBits() override;
private:
	std::string bitShift = ""; // 2 bits should usually be 00
	std::string usingImmediate = ""; // 1 bit
	std::string operationCode = ""; // 4 bits
	std::string usingSBit = ""; // 1 bit
	std::string firstOpperandRegister = ""; // 4 bits
	std::string secondOpperand = ""; // 12 bits
};