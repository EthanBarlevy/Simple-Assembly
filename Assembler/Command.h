#pragma once
#include <bitset>
#include <vector>

class Command
{
public:
	Command(std::string code, std::string registry);
	virtual std::vector<std::bitset<8>>* GetBits() { return new std::vector<std::bitset<8>>(); }
public:
	std::string ConditionCode = "";
	std::string Register = "";
};

