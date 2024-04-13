#include "Hex.h"

std::string Hex::GetHex(std::bitset<4> binary)
{
	std::stringstream hex;
	hex << std::hex << binary.to_ulong();
	return hex.str();
}
