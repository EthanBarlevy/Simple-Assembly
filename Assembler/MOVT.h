#pragma once
#include "Command.h"

class MOVT : public Command
{
public:
	MOVT();
	std::string ConvertToHex() override;
	void setImmediate(std::string& immediate);
public:
	Binary* imm4 = new Binary();
	Binary* imm12[3];
	Binary* c = new Binary();
	Binary* q = new Binary();
};