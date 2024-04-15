#pragma once
#include "Command.h"

class SingleDataTransfer : public Command
{
public:
	std::bitset<8>* GetBits() override;
private:
	std::string bitShift = ""; // 2 bits should usually be 01
	std::string usingImmediate = ""; // 1 bit
	std::string indexingBit = ""; // 1 bit
	std::string upBit = ""; // 1 bit
	std::string wordBit = ""; // 1 bit
	std::string writeBackBit = ""; // 1 bit
	std::string loadStoreBit = ""; // 1 bit
	std::string firstOpperandRegister = ""; // 4 bits
	std::string secondOpperand = ""; // 12 bits
};