#pragma once
#include <iostream>
#include <sstream>
#include <bitset>

class Binary {
public:
	void SetBinary(std::string binary);
	std::bitset<4> GetBinary();
public:
	std::bitset<4>* bin;
};