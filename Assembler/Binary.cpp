#include "Binary.h"

void Binary::SetBinary(std::string binary)
{
    bin = new std::bitset<4>(binary);
}

std::bitset<4> Binary::GetBinary()
{
    return *bin;
}
