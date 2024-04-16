#pragma once
#include "Command.h"

class MOVE : public Command
{
public:
	enum Half
	{
		FRONT,
		BACK
	};
	MOVE(std::string code, std::string registry);
	MOVE(std::string code, std::string registry, Half side);
	MOVE(std::string code, Half side, std::string im4, std::string registry, std::string im12);
	std::vector<std::bitset<8>>* GetBits() override;
public:
	std::string imm4 = "";
	std::string imm12 = "";
	std::string c = "";
	std::string q = "";
};

