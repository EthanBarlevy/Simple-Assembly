#pragma once
#include "Binary.h"
#include "Hex.h"

class Command
{
public:
	virtual std::string ConvertToHex() = 0;
public:
	Binary* ConditionCode = new Binary();
	Binary* Register = new Binary();
};