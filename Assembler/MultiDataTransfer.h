#pragma once
#include "Command.h"

#include "Command.h"

class MultiDataTransfer : public Command
{
public:
	MultiDataTransfer(std::string code, std::string registry, std::string iBit, std::string uBit, std::string pBit, std::string wBit, std::string lBit, std::string registers);
	std::vector<std::bitset<8>>* GetBits() override;
private:
	std::string indexingBit = ""; // 1 bit
	std::string upBit = ""; // 1 bit
	std::string PSRBit = "0"; // 1 bit
	std::string writeBackBit = ""; // 1 bit
	std::string loadStoreBit = ""; // 1 bit
	std::string registerList = ""; // 16 bits
};