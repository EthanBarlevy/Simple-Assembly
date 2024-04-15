#include "SingleDataProcessing.h"

std::bitset<8>* SingleDataProcessing::GetBits()
{
    static std::bitset<8> bits[4];
    std::string bitstring = ConditionCode + bitShift + usingImmediate + operationCode + usingSBit + firstOpperandRegister + Register + secondOpperand;
    bits[3] = std::bitset<8>(bitstring.substr(0,8));
    bits[2] = std::bitset<8>(bitstring.substr(8, 8));
    bits[1] = std::bitset<8>(bitstring.substr(16, 8));
    bits[0] = std::bitset<8>(bitstring.substr(24, 8));
    return bits;
}
