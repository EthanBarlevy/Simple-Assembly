#pragma once
#include "Command.h"

class MOVE : public Command
{
public:
	enum Half
	{
		FRONT,
		BACK,
		W,
		T
	};
	MOVE();
	MOVE(Half side);
	std::bitset<8>* GetBits() override;
	void setImmediate(std::string& immediate);
public:
	std::string imm4 = "";
	std::string imm12[3];
	std::string c = "";
	std::string q = "";
};

