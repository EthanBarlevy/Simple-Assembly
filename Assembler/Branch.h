#pragma once
#include "Command.h"

class Branch : public Command
{
public:
	std::bitset<8>* GetBits() override;
private:
	std::string lBit = "";
	std::string offset = "";
};