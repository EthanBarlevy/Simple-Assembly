#pragma once
#include <iostream>
#include <sstream>
#include <bitset>

class Hex{
public:
	static std::string GetHex(std::bitset<4> binary);
};