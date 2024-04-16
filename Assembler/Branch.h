#pragma once
#include "Command.h"

class Branch : public Command
{
public:
	Branch(std::string code, std::string registry, std::string usingLBit, std::string offsets);
	std::vector<std::bitset<8>>* GetBits() override;
private:
	std::string lBit = "";
	std::string offset = "";
};